#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct stat STAT;


void process(int fd) {
    STAT st;
    unsigned long long count = 0;

    if (fd == -1) {
        printf("-1\n");
        return;
    }

    if (fstat(fd, &st) == -1) {
        close(fd);
        printf("-1\n");
        return;
    }

    if (!st.st_size) {
        close(fd);
        printf("0\n");
        return;
    }

    void * ptr = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        close(fd);
        printf("-1\n");
        return;
    }

    char * mptr = (char *) ptr;
    for (long i = 0; i < st.st_size; ++i)
        if (mptr[i] == '\n') ++count;

    if (mptr[st.st_size - 1] != '\n') ++count;

    printf("%llu\n", count);
    close(fd);
    munmap(ptr, st.st_size);

}

int main(int argc, char ** argv) {
    for (int j = 1; j < argc; ++j) {
        process(open(argv[j], O_RDONLY));
    }

    return 0;
}
