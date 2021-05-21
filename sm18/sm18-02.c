#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int cnt = 0;

int sqr (int a) {
    int res = a * a;
    return res;
}
int ot(int a) {
    int res = -1;
    res *= a;
    return res;
}
volatile int (*func) (int) = ot;

void sqrt_handler(int signo) {
    func = sqr;
}
void ot_handler(int signo) {
    func = ot;
}


int main(void) {
    struct sigaction ot_s = {
            .sa_handler = ot_handler,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &ot_s, NULL);

    struct sigaction sqrt_s = {
            .sa_handler = sqrt_handler,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR2, &sqrt_s, NULL);

    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    int n = 0;
    while (scanf("%d", &n) == 1) {
        printf("%d\n", func(n));
        fflush(stdout);
    }
    return 0;
}
