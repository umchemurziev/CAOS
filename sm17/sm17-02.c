#include <inttypes.h>
#include <stdint.h>
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
    if (pid1) {
        close(fd[0]);

        int32_t val;
        while(scanf("%" SCNd32, &val) == 1) {
            write(fd[1], &val, sizeof(val));
        }
        close(fd[1]);
        while(wait(NULL) != -1) {}
        exit(0);
    } // else {}

    close(fd[1]);

    pid_t pid2 = fork();
    if (pid2 < 0) {
        exit(1);
    }

    if (!pid2) {
        int32_t val;
        int64_t sum = 0;
        
        while(read(fd[0], &val, sizeof(val)) == sizeof(val)) {
            sum += val;
        }
        printf("%"PRId64"\n", sum);
        close(fd[0]);
        exit(0);
    } // else {}

    close(fd[0]);
    wait(NULL);
    return 0;
}
// Решение взял с семинара
