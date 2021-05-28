#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>


enum { TH = 1000, ML = 1000000};


void handler(int n) {
    (void)n;
    exit(0);
}

int main(void) {
    time_t a;
    long b;
    scanf("%ld %ld", &a, &b);

    struct sigaction sa = {};
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    struct timeval act = {};
    gettimeofday(&act, NULL);

    long sec = a - act.tv_sec;
    long us = b / TH - act.tv_usec;
    long tmt = TH * TH * sec + us;
    if (tmt < 0) exit(0);

    struct itimerval till = {};
    till.it_value.tv_sec = tmt / ML;
    till.it_value.tv_usec = tmt % ML;

    setitimer(ITIMER_REAL, &till, NULL);
    pause();

    return 0;
}
