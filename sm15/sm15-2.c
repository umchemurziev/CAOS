#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    for (int id = 1; id < 4; ++id) {
        pid_t pid = fork();
        if (!pid) {
            char str[8];
            read(0, str, 8);
            int32_t num = strtol(str, NULL, 10);
            printf("%d %" PRId32 "\n", id, num * num);
            return 0;
        }

        wait(NULL);
        wait(NULL);
        wait(NULL);
    }
}
