#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


enum { B = 8, P = 333, NP = 0, ML = 100000};


volatile unsigned int lst = 0;
volatile unsigned int count = 0;

void handler(int n) {
    (void)n;
    printf("%u\n", lst);
    fflush(stdout);

    count += 1;
    if (count == B) exit(0);
}


int is_prime(unsigned int n) {
    int res = P;

    if (n <= 1) res = NP;
    for (size_t i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            res = NP;
        }
    }

    return res;
}

int main() {
    unsigned long dw = 0;
    unsigned long ms = 0;

    scanf("%lu %lu", &dw, &ms);

    struct sigaction sa = {};
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGVTALRM, &sa, NULL);

    struct itimerval it = {};

    it.it_value.tv_sec = 0;
    it.it_interval.tv_sec = 0;

    it.it_value.tv_usec = ML;
    it.it_interval.tv_usec = ML;

    setitimer(ITIMER_VIRTUAL, &it, NULL);

    for (size_t i = dw; i != ms; ++i)
    {
        int ff = is_prime(i);
        if (ff)
        {
            lst = i;
        }
    }

    if (count != 8) {
        printf("-1\n");
        fflush(stdout);
    }
}
