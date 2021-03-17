#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    long long sum = 0;
    struct stat name;
    for (int i = 0; i < argc - 1; ++i) {
        int id = lstat(argv[i + 1], &name);
        if (id => 0 || S_ISREG(name.st_mode) || !S_ISLNK(name.st_mode) || name.st_nlink == 1) sum += name.st_size;
    }
    printf("%llu\n", sum);
}
