#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int proc(char **a, int i) {
    pid_t pid = fork();
    int status;
    if (!pid) {
        execlp(a[i], a[i], NULL);
        return 0;
    } else {
        wait(&status);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main(int _, char ** a) {
    if (proc(a, 1) || proc(a, 2)) {
        if (proc(a, 3)) {
            return 0;
        } else  {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
