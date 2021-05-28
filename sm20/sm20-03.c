#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>


enum { TJ = 4096, LS = 3, MT = 2 };


char* check(int n, char* num, int bs) {
	printf("%d %s\n", n, num);
    fflush(stdout);

    int len = strlen(num);
    char right = 1;
    for (int i = 0; i != len; ++i) {
        num[i] += right;
        if (num[i] == '0' + bs) {
            num[i] = '0';
            right = 1;
        } else {
            right = 0;
        }
    }
    if (right) {
        num[len] = '1';
        num[len + 1] = '\0';
    }
    return num;
}


int main(int argc, char* argv[])
{
	char* num = NULL;
	int* cnt = NULL;
	int bs = 0;
	int fd[MT];


    int n = atoi(argv[1]);
    bs = atoi(argv[MT]);

    void* data = mmap(NULL, TJ * sizeof(char) + sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    cnt = data;
    *cnt = 1;

    num = data + sizeof(int);

    strcpy(num, argv[LS]);

    fd[0] = eventfd(0, EFD_SEMAPHORE);
    fd[1] = eventfd(0, EFD_SEMAPHORE);

    if (n)
    {
    	pid_t pid = fork();
        if (!pid)
        {
            uint64_t t = 1;
            check(1, num, bs);

            write(fd[1], &t, sizeof(t));

            while ((*cnt) != n)
            {
                read(fd[0], &t, sizeof(t));
                check(1, num, bs);

                write(fd[1], &t, sizeof(t));
            }

            exit(0);
        }

        pid_t pid2 = fork();
        if (!pid2)
       {
            uint64_t t = 0;

            while ((*cnt) != n)
            {
                read(fd[1], &t, sizeof(t));
                check(MT, num, bs);

                write(fd[0], &t, sizeof(t));
            }

            exit(0);
        }

        waitpid(-1, NULL, 0);
        waitpid(-1, NULL, 0);
    }

    printf("Done\n");

    munmap(data, TJ * sizeof(char) + sizeof(int));
}
