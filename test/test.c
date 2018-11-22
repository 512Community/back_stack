#include <stdio.h>
#include <put_crash.h>

int main(int argc, const char *argv[])
{
	char *p = NULL;
	catch_crash_stack();

	*p = 1;

	return 0;
}
