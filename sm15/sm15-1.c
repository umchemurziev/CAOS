#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main () {
    pid_t pid = fork();
    

    if (pid) {
        wait(NULL);
        printf("%d\n", 1);
    } else {
        pid_t pid1 = fork();

        if (pid1) {
            wait(NULL);
            printf("%d ", 2);
        } else {
            printf("%d ", 3);
        }
    }

    return 0;
}
