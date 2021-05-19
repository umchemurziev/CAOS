#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <sys/mman.h>


int main (int argc, char * argv[]) {
	int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 1) {
		return 1;
	}
	int rows = strtol(argv[2], NULL, 10);
	int cols = strtol(argv[3], NULL, 10);
	long len = rows * cols * sizeof(double);
	if (ftruncate(fd, len) == -1) {
		return 1;
	}

	void *av = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fd, 0);
	if (av == MAP_FAILED) {
		return 1;
	}
	double (*matrix)[cols] = av;
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			double a = sin((double) i);
			double b = cos((double) j / 2);
			matrix[i][j] = 2 * a + 4 * b;
		}
	}
	munmap(av, len);
	close(fd);
}