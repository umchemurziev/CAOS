#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


void mykill(int *children, int size) {
    for (int i = 1; i < size; ++i)
        kill(children[i], SIGKILL);
    _exit(1);
}

int main(int argc, char **argv) {
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0) _exit(1);
    pid_t ch[argc];
    pid_t pid = fork();
    ch[1] = pid;

    if (pid < 0) _exit(1);
    else if (!pid)
    {
        close(pipe_fd[0]);

        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        execlp(argv[1], argv[1], NULL);
    }

    close(pipe_fd[1]);

    int pipe_in = pipe_fd[0];

    for (size_t i = 2; i != argc; ++i)
    {
        if (pipe(pipe_fd) < 0)
            mykill(ch, i);

        ch[i] = fork();

        if (ch[i] < 0) {
            mykill(ch, i);
        }
        else if (!ch[i])
        {
            if (i + 1 < argc)
            {
                dup2(pipe_fd[1], 1);
                close(pipe_fd[1]);
            }

            dup2(pipe_in, 0);
            close(pipe_in);

            if (i + 1 < argc)
                close(pipe_fd[0]);

            execlp(argv[i], argv[i], NULL);
        }
        close(pipe_in);
        if (i + 1 == argc)
        {
            close(pipe_fd[0]);
            break;
        }

        close(pipe_fd[1]);
        pipe_in = pipe_fd[0];
    }

    for (size_t i = 1; i != argc; ++i)
        waitpid(-1, NULL, 0);
}
