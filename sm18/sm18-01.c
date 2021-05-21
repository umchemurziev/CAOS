#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

enum { END = 4 };

volatile int cnt = 0;

void sigint_handler(int signo) {
    printf("%d\n", cnt);
    fflush(stdout);
    if (++cnt >= END) {
        _exit(0);
    }
}

int main(void) {
    struct sigaction s = {
        .sa_handler = sigint_handler,
    };

    sigaction(SIGINT, &s, NULL);
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    while (true) {
        pause();
    }
}
