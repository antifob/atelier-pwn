#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>


static void die(const char* str)
{
	int l = strlen(str);

	write(1, str, l);
	exit(1);
}


static void PUTS(const char* str)
{
	int l = strlen(str);

	if (l != write(1, str, l)) {
		die("write");
	}
}


int main(int argc, const char* const* argv)
{
	char buf[256];
	void (*p)(void);

	PUTS("Gimme shellcode. Get the flag at flag.txt\n");
	PUTS("Here are the parameters:\n\n");
	PUTS(" - maximum length: 256 bytes\n");
	PUTS(" - filtered bytes: none\n");
	PUTS(" - other constraints: none\n\n");
	PUTS("your shellcode>");

	if (0 >= read(0, buf, sizeof(buf))) {
		return 0;
	}

	if (MAP_FAILED == (p = mmap(0, sizeof(buf), 7, 0x22, -1, 0))) {
		die("mmap");
	}
	memcpy(p, buf, sizeof(buf));
	if (0 != mprotect(p, sizeof(buf), (PROT_READ | PROT_EXEC))) {
		die("mprotect");
	}

	p();

	return 0;
}