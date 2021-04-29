#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t pid = fork();
    if (pid) {
        wait(NULL);
    } else {
        int fd_in = open(argv[2], O_RDONLY);
        int fd_out = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0666);

        dup2(fd_in, 0);
        dup2(fd_out, 1);

        close(fd_in);
        close(fd_out);

        if (execlp(argv[1], argv[1], (char *) 0) == -1) {
            fprintf(stderr, "bruh\n");
            exit(1);
        }
    }
}
// Решение взял с семинара
