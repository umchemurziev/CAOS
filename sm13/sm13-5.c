#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

struct Data
{
    unsigned char arguments[64];
};

int main(int args, char *argv[]) {
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    void *func = dlsym(handle, argv[2]);
    if (!func) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    struct Data x;
    int cur = 0;
    double tmp1;
    int tmp2;
    for (size_t i = 4; i < args; ++i) {
        char argument = argv[3][i-3];
        
        if (argument == 'd') {
            tmp1 = strtod(argv[i], NULL);
            memcpy(x.arguments + cur, &tmp1, sizeof(double));
            cur += sizeof(double);
        } else if (argument == 'i') {
            tmp2 = strtol(argv[i], NULL, 10);
            memcpy(x.arguments + cur, &tmp2, sizeof(int));
            cur += sizeof(int);
        } else {
            memcpy(x.arguments + cur, argv + i, sizeof(char*));
            cur += sizeof(char*);
        }
    }
    if (argv[3][0] == 'v') {
        ((void (*)(struct Data))func)(x);
    } else if (argv[3][0] == 's') {
        printf("%s\n", ((char *(*)(struct Data))func)(x));
    } else if (argv[3][0] == 'd') {
        printf("%.10g\n", ((double (*)(struct Data))func)(x));
    } else {
        printf("%d\n", ((int (*)(struct Data))func)(x));
    }
    if (dlclose(handle) != 0) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    return 0;
}
