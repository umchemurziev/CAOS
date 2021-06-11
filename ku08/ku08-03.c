#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void foo(int n, int fd_r, int fd_w, int is_two, double tmp, double send, double amount, double b)
{
    for (size_t i = 0; i < n + 1; ++i)
    {
        if (!is_two)
        {
            send = sin(tmp);
        }
        else
        {
            send = cos(tmp);
        }
        tmp += b;
        write(fd_w, &send, sizeof(send));
        read(fd_r, &send, sizeof(send));
        if (!is_two) {
            amount += send * send;
        } else
            amount += fabs(send);
    }
    if (is_two)
    {
        printf("2 %.11g\n", amount);
    }
    else
    {
        printf("1 %.11g\n", amount);
    }

    fflush(stdout);
}

void cls(int *fd)
{
    close(fd[0]);
    close(fd[1]);
}

int main(int argc, char* argv[])
{
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[3], NULL);

    int fd1[2] = { 0 };
    int fd2[2] = { 0 };
    int n = atoi(argv[2]);

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        return 1;
    }

    pid_t pid = fork();
    if (!pid)
    {
        pid_t child = fork();
        if (!child)
        {
            foo(n, fd1[0], fd2[1], 0, a, 0.0, 0.0, b);

            cls(fd1);
            cls(fd2);

            exit(0);
        }

        cls(fd1);
        cls(fd2);

        wait(NULL);

        exit(0);
    }

    pid = fork();
    if (!pid) {

        pid_t child = fork();
        if (!child)
        {
            foo(n, fd2[0], fd1[1], 1, a, 0.0, 0.0, b);

            cls(fd1);
            cls(fd2);

            exit(0);
        }

        cls(fd1);
        cls(fd2);

        wait(NULL);

        exit(0);
    }

    cls(fd1);
    cls(fd2);

    while (wait(NULL) > 0);

    printf("0 0\n");

    return 0;
}
