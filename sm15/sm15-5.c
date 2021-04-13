#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc >= 6) {
        size_t N = atoi(argv[1]);
        char *file = argv[2];
        int A0 = atoi(argv[3]);
        int D = atoi(argv[4]);
        int K = atoi(argv[5]);
        int fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0600);
        pid_t *pids = malloc(sizeof(pid_t) * N);
        if (fd == -1 || close(fd) == -1) return 1;
        for (int i = 0; i < N; ++i) {
            pids[i] = fork();
            if (pids[i] < 0) return 1;
            if (!pids[i]) {
                int fd = open(file, O_RDWR);
                if (fd == -1) return 1;

                int temp = A0 + i * D;
                int ND = K * N;
                int j = 0;
                while (j < ND) {
                    lseek(fd, (i + j) * sizeof(int), SEEK_SET);
                    write(fd, &temp, 1 * sizeof(int));
                    temp += N * D;
                    j += N;
                }
                close(fd);
                return 0;
            }
        }
        for (int i = 0; i < N; ++i) {
            waitpid(pids[i], NULL, 0);
        }
        free(pids);
    }
}
