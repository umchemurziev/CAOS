#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    pid_t prev = getpid();
    int num;
    while (scanf("%d", &num) != EOF) {
        pid_t pid = fork();
        if (pid < 0) return 1;
        if (pid) {
            int st;
            waitpid(pid, &st, 0);
            pid_t temp = getpid();
            if (st && temp == prev) {
                printf("%d\n", -1);
                break;
            }
            if (!st) {
                printf("%d\n", num);
                break;
            }
            return 1;
        }
    }
}
