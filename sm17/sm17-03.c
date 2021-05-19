#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    int status = 0;
    if (argc < 4) {
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) exit(1);
    pid_t pid1 = fork();
    if (pid1 < 0) exit(1);

    if (!pid1) {
        close(pipe_fd[0]);

        pid_t pid2 = fork();
        if (pid2 < 0) exit(1);
        if (!pid2) {
            dup2(pipe_fd[1], 1);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execlp(argv[1], argv[1], NULL);
            _exit(0);
        }
        status = 0;
        wait(&status);

        pid_t pid3 = fork();
        if (pid3 < 0) exit(1);
        if (!pid3)
        {
            dup2(pipe_fd[1], 1);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execlp(argv[2], argv[2], NULL);
            _exit(0);
        }
        close(pipe_fd[1]);
        status = 0;
        wait(&status);
        _exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 < 0) exit(1);
    if (!pid4)
    {
        dup2(pipe_fd[0], 0);
        int file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(file, 1);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(file);
        execlp(argv[3], argv[3], NULL);
        _exit(0);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    status = 0;
    while (wait(&status) > 0)
    {
        status = 0;
    }
}
