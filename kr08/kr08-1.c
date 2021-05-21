#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;

void s1_handler (int signo) {
    printf("%d %d\n", signo, cnt);
    fflush(stdout);
    cnt += 2;
}

void s2_handler (int signo) {
    printf("%d %d\n", signo, cnt);
    fflush(stdout);
    cnt -= 3;
    if (cnt < 0) _exit(0);
}

int main() {
    struct sigaction sig1 = {
            .sa_handler = s1_handler,
            .sa_flags = SA_RESTART
    };
    sigaction(SIGUSR1, &sig1, NULL);

    struct sigaction sig2 = {
            .sa_handler = s2_handler,
            .sa_flags = SA_RESTART
    };
    sigaction(SIGUSR2, &sig2, NULL);
    
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    while (true) {
        pause();
    }
    return 0;
}
