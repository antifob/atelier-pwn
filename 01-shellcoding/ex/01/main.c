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
	int f[2];
	char buf[256];
	void (*p)(void);

	PUTS("Gimme shellcode. Get a flag\n");
	PUTS("Your shellcode must write \"I know how to shellcode\" to descriptor 4 and return\n");
        PUTS("Here are the parameters:\n\n");
        PUTS(" - maximum length: 256 bytes\n");
        PUTS(" - filtered bytes: none\n");
        PUTS(" - other constraints: none\n\n");
	PUTS("your shellcode>");

	if (0 != pipe(f)) {
		die("pipe");
	}

	if (0 >= read(0, buf, sizeof(buf))) {
		die("read");
	}

	if (MAP_FAILED == (p = mmap(0, sizeof(buf), 7, 0x22, -1, 0))) {
		die("mmap");
	}
	memcpy(p, buf, sizeof(buf));
	if (0 != mprotect(p, sizeof(buf), (PROT_READ | PROT_EXEC))) {
		die("mprotect");
	}

	p();

	if (0 >= read(3, buf, sizeof(buf))) {
		die("read");
	}
	if (strncmp("I know how to shellcode", buf, 23)) {
		PUTS("Try again!\n");
	} else {
		PUTS("FLAG-de790daa31cd3848b254435db64dc3aa\n");
	}

	return 0;
}
