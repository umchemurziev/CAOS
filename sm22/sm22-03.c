#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


enum
{
    LM = 1000, SZ = 100
};

struct Item
{
    struct Item *next;
    long long value;
};


struct Item *_Atomic root = NULL;
void *calc(void *ptr)
{
    size_t c = 0;
    while (c < LM)
    {
        struct Item *tr = calloc(0, sizeof(struct Item));

        tr->value = (long) ptr + c;
        tr->next = atomic_exchange(&root, tr);

        sched_yield();
        ++c;
    }

    return NULL;
}

int main(void)
{
    pthread_t cnts[SZ] = { 0 };

    pthread_attr_t hap;
    pthread_attr_init(&hap);
    pthread_attr_setstacksize(&hap, sysconf(_SC_THREAD_STACK_MIN));

    size_t c = 0;
    while (c < SZ)
    {
        pthread_create(&cnts[c], &hap, calc, (void *) ((long) c * LM));
        ++c;
    }

    pthread_attr_destroy(&hap);

    c = 0;
    while (c < SZ)
    {
        pthread_join(cnts[c], NULL);
        ++c;
    }

    while (root)
    {
        struct Item *tr = root;
        printf("%lld\n", root->value);
        root = root->next;
        free(tr);
    }

    return 0;
}
