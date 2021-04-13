#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        if (i < n) printf("%d ", i);
        if (i == n) printf("%d\n", i);
        fflush(stdout);
        pid_t pid = fork();
        if (i == n) return 0;
        if (pid) {
            wait(NULL);
            return 0;
        }
    }
}