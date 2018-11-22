#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <execinfo.h>
#include  <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BACKTRACE_SIZE   16
static char filename[64];

static void addr2line(char *string)
{
	char *pos1, *pos2;
	char addr[16], cmd[64];

	bzero(&addr, sizeof(addr));
	bzero(&cmd, sizeof(cmd));
	pos1 = strchr(string, '[') + 1;
	pos2 = strchr(string, ']');
	memcpy(addr, pos1, pos2 -pos1);
	sprintf(cmd, "addr2line -e %s %s", filename, addr);
	printf("\033[31m");
	fflush(stdout);
	system(cmd);
	printf("\033[0m\n");
}

static void dump(void)
{
	int j, nptrs;
	void *buffer[BACKTRACE_SIZE];
	char addr[64];
	char cmd[64];
	char **strings;

	nptrs = backtrace(buffer, BACKTRACE_SIZE);

	printf("backtrace() returned %d addresses\n", nptrs - 3);

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (j = 3; j < nptrs; j++) {
		printf("[%02d] %s\n", j - 3, strings[j]);
		addr2line(strings[j]);
	}

	free(strings);
}

static void get_proc_maps(void)
{
	char buff[64] = {0x00};
	sprintf(buff,"cat /proc/%d/maps", getpid());
	system((const char*) buff);
}
static void signal_handler(int signo)
{
	get_proc_maps();

	printf("\n=========>>>catch signal %d <<<=========\n", signo);
	printf("Dump stack start...\n");
	dump();
	printf("Dump stack end...\n");

	signal(signo, SIG_DFL);
	raise(signo);
}

static void get_proc_name(void)
{
	int fd;
	char name[64] = {0x00};
	sprintf(name,"/proc/%d/cmdline", getpid());
	fd = open(name, 0666);
	if (fd < 0) {
		perror("open cmdline failed");
		return ;
	}

	if(read(fd, filename, 64) < 0) {
		perror("backtrace_symbols");
	}

	close(fd);
}

void catch_crash_stack()
{
	get_proc_name();
	signal(SIGSEGV, signal_handler);
}

