#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


enum
{
    DB = 2
};

int *fds = NULL;
int count = 0;

void *thread_func(void * ptr) {
    int num = *((intptr_t *) ptr);
    int ft = 0;
    int tr = 0;

    while (true)
    {
        read(fds[DB * num], &tr, sizeof(tr));

        int scn = scanf("%d", &ft);
        if (scn == 1) {
            printf("%d %d\n", num, ft);
            fflush(stdout);

            ft %= count;
            if (ft < 0)
            {
                ft += count;
            }

            write(fds[DB * ft + 1], &ft, sizeof(ft));
            fflush(stdout);
        } else {
            ft = (num + 1) % count;
            write(fds[DB * ft + 1], &ft, sizeof(ft));
            fflush(stdout);
            break;
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{   
    if (argc <= 1) return 0;

    count = strtol(argv[1], NULL, 10);

    pthread_t ids_a[count];
    int fds_a[DB * count];

    pthread_t *ids = ids_a;
    fds = fds_a;

    int pids[count];

    size_t c = 0;
    while (c < count)
    {
        pids[c] = c;
        pipe(&(fds[DB * c]));
        ++c;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));

    c = 0;
    while (c < count)
    {
        pthread_create(&ids[c], &attr, thread_func, &pids[c]);
        ++c;
    }

    int t = 0;
    write(fds[1], &t, sizeof(t));

    c = 0;
    while (c < count)
    {
        pthread_join(ids[c], NULL);
        ++c;
    }

    c = 0;
    while (c < count)
    {
        close(fds[DB * c]);
        close(fds[DB * c + 1]);
        ++c;
    }

    pthread_attr_destroy(&attr);

    return 0;
}
