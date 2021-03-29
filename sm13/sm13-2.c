#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    void *lib = dlopen("/lib/libm.so.6", RTLD_LAZY);
    if (!lib) {
        printf("%s\n", dlerror());
    }

    void *func = dlsym(lib, argv[1]);
    if (!func) {
        printf("%s\n", dlerror());
    }

    double ans;
    while (scanf("%lf", &ans) != EOF) {
        printf("%.10g\n", ((double(*)(double)) func)(ans));
    }

    dlclose(lib);
    return 0;
}
