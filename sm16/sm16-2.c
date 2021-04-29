#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


int mysys(const char *str) {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        }
        return -1;
    }
}
// Решение взял с семинара 
