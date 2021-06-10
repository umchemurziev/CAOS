#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *cal(void *ptr)
{
    int num = 0;
    long long *sum = ptr;

    *sum = 0;
    while (scanf("%d", &num) > 0)
    {
        (*sum) += num;
        sched_yield();
    }

    return NULL;
}

int main(int argc, char **argv)
{

	if (argv[1] == 0) return 0;

	long long ans = 0;
    int n = atoi(argv[1]);

    pthread_t hreads[n];
    long long calc[n];

    pthread_attr_t hap;
    pthread_attr_init(&hap);
    pthread_attr_setstacksize(&hap, sysconf(_SC_THREAD_STACK_MIN));

    size_t count = 0;
    while (count <= n - 1)
    {
        pthread_create(&hreads[count], &hap, cal, calc + count);
        ++count;
    }
    pthread_attr_destroy(&hap);


    count = 0;
    while (count <= n - 1)
    {
        pthread_join(hreads[count], NULL);
        ans += calc[count];
        ++count;
    }

    printf("%lld\n", ans);
    fflush(stdout);

    return 0;
}
