#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2];
    if (pipe(fd) == -1) {
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        exit(1);
    }
    if (!pid1) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        // child 1
        // pipe: 1
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }

    close(fd[1]);

    pid_t pid2 = fork();
    if (pid2 < 0) {
        exit(1);
    }
    if (!pid2) {
        dup2(fd[0], 0);
        // pipe: 0 fd[0]
        close(fd[0]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    // parent
    // fd[0] fd[1]
    close(fd[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
// Решение взял с семинара
