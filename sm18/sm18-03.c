#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;
volatile int s1 = 0;
volatile int s2 = 0;

void trm_handler(int signo) {
    _exit(0);
}
void s1_handler(int signo) {
    s1 = 1;
}
void s2_handler(int signo) {
    s2 += 1;
}


int main(void) {
    sigset_t set;
    sigset_t zer;

    sigemptyset(&set);
    sigemptyset(&zer);

    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGTERM);

    sigprocmask(SIG_BLOCK, &set, NULL);

    struct sigaction s_1 = {
            .sa_handler = s1_handler,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &s_1, NULL);

    struct sigaction s_2 = {
            .sa_handler = s2_handler,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR2, &s_2, NULL);


    struct sigaction s_term = {
            .sa_handler = trm_handler,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGTERM, &s_term, NULL);

    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);

    int c = 0;
    while (true) {
        sigsuspend(&zer);
        if (s1) {
            printf("%d %d\n", c++, s2);
            fflush(stdout);
            s1 = 0;
        };
    }
    return 0;
}
