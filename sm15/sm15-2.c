#include <inttypes.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    for (int id = 1; id < 4; ++id) {
        pid_t pid = fork();
        if (pid) {
            wait(NULL);
        } else {
            int32_t num;
            scanf("%d", &num);
            printf("%d %" PRId32 "\n", id, num * num);
            return 0;
        }
    }
}

