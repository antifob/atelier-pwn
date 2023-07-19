#define _XOPEN_SOURCE 0700

#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>


int main(int argc, const char* const* argv)
{
	int fd;
	struct stat st;
	void (*p)(void);


	if (2 != argc) {
		fprintf(stderr, "usage: %s sc.bin\n", argv[0]);
		return 1;
	}

	if (0 != stat(argv[1], &st)) {
		perror("stat");
		return 1;
	}

	if (0 > (fd = open(argv[1], O_RDONLY))) {
		perror("open");
		return 1;
	}

	if (MAP_FAILED == (p = mmap(0, st.st_size, (PROT_READ | PROT_EXEC), MAP_PRIVATE, fd, 0))) {
		perror("mmap");
		return 1;
	}

	p();

	return 0;
}
