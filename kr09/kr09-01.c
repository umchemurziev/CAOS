#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


enum
{
    SZ = 4
};

void* calc (void *ptr)
{
    int n = *(int *) ptr;
    printf("%d\n", n);
    return NULL;
}

int main (int argc, char **argv)
{
    if (argc <= 4) return 0;

    pthread_t threads[SZ];
    int c[SZ] = { 0 };

    for (size_t i = 0; i < SZ; ++i)
    {
        c[i] = strtol(argv[i + 1], NULL, 10);
    }
    
    int c2[SZ] = { 0 };

    for (int i = 0; i < SZ; ++i)
    {
        if (c[i] == 4)
        {
            c2[3] = i + 1;
            break;
        }
    }
    for (int i = 0; i < SZ; ++i)
    {
        if (c[i] == 3)
        {
            c2[2] = i + 1;
            break;
        }
    }
    for (int i = 0; i < SZ; ++i)
    {
        if (c[i] == 2)
        {
            c2[1] = i + 1;
            break;
        }
    }
    for (int i = 0; i < SZ; ++i)
    {
        if (c[i] == 1)
        {
            c2[0] = i + 1;
            break;
        }
    }
    c[0] = c2[0];
    c[1] = c2[1];
    c[2] = c2[2];
    c[3] = c2[3];

    for (size_t i = 0; i < SZ; ++i)
    {
        pthread_create(&threads[i], NULL, calc, &c[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}
