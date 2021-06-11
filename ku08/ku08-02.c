#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void foo(long int n, int fd, int cnt)
{
    long int num = 0;
    while (scanf("%ld", &num) != EOF)
    {
        if (num - 1 == n) break;
        printf("%d %ld\n", cnt, num);
        ++num;
        fflush(stdout);
        dprintf(fd, "%ld\n", num);
    }
    close(fd);
}

int main(int argc, char **argv)
{
    int fd1[2] = { 0 };
    int fd2[2] = { 0 };
    int fd3[2] = { 0 };
    int pipe1 = pipe(fd1);
    int pipe2 = pipe(fd2);
    int pipe3 = pipe(fd3);

    if (pipe1 == -1)
    {
        exit(1);
    }
    else if (pipe2 == -1)
    {
        exit(1);
    }
    else if (pipe3 == -1)
    {
        exit(1);
    }

    char *pEnd;
    long int n = strtol(argv[1], &pEnd, 10);

    pid_t pid = fork();
    if (!pid)
    {
        close(fd1[1]);
        close(fd3[0]);

        pid_t child_pid = fork();
        if (!child_pid)
        {
            close(fd1[0]);
            close(fd2[1]);
            dup2(fd2[0], 0);

            foo(n, fd3[1], 3);
            close(fd2[0]);

            exit(0);
        }

        close(fd2[0]);
        close(fd3[1]);
        dup2(fd1[0], 0);

        foo(n, fd2[1], 2);
        close(fd1[0]);

        exit(0);
    }

    dprintf(fd3[1], "1\n");

    close(fd2[0]);

    close(fd2[1]);

    dup2(fd3[0], 0);
    close(fd3[0]);
    close(fd3[1]);

    foo(n, fd1[1], 1);
    close(fd1[0]);
    close(fd1[1]);

    while (wait(NULL) > 0);

    return 0;
}
