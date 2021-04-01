#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        return 1;
    }
    size_t size = st.st_size;
    int len = size / sizeof(double);
    if (len > 0) {
        void *data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (data == MAP_FAILED) {
            return 1;
        }
        double sum = 0.;
        double* data_double = (double*) data;
        for (int i = 0; i < len ; i++) {
            sum += data_double[i];
        }
        munmap(data, size);
        printf("%a\n", sum / len);
    } else {
        printf("%a\n", 0.);
    }
    close(fd);
    return 0;
}
//  Взял с семинара
