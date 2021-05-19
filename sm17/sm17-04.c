#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void proc(FILE * r_r, FILE * r_w, FILE * l_r, FILE * l_w, long des, int r) {
    long long cl = 0;
    if (r) {
        fclose(r_w);
        fclose(l_r);
        
        while (fscanf(r_r, "%lld", &cl) != EOF && cl != des) {
            printf("1 %lld\n", cl);
            cl += 1;
            fprintf(l_w, "%lld\n", cl);
            fflush(l_w);
            fflush(stdout);
        }
        fclose(r_r);
        fclose(l_w);

        exit(0); 
    }
    
    fclose(l_w);
    fclose(r_r);

    fprintf(r_w, "1\n");
    fflush(r_w);

    while (fscanf(l_r, "%lld", &cl) != EOF && cl != des) {
        printf("2 %lld\n", cl);
        cl += 1;
        fprintf(r_w, "%lld\n", cl);
        fflush(r_w);
        fflush(stdout);
    }

    fclose(r_w);
    fclose(l_r);

    exit(0);
}


int main(int argc, char * argv[]) {
    if (argc < 2) return 1;
    int left[2];
    int right[2];

    long long des = strtol(argv[1], NULL, 10);
    if (des < 2)
    {
        printf("Done\n");
        return 0;
    }
    if (pipe(right) == -1) exit(1);
    if (pipe(left) == -1) exit(1);
    
    
    FILE * right_read = fdopen(right[0], "r");
    FILE * right_write = fdopen(right[1], "w");
    FILE * left_read = fdopen(left[0], "r");
    FILE * left_write = fdopen(left[1], "w");



    pid_t pid1 = fork();
    if (pid1 < 0) exit(1);
    if (!pid1) {
        proc(right_read, right_write, left_read, left_write, des, 1);
    }
    
    pid_t pid2 = fork();
    if (pid2 < 0) exit(1);
    if (!pid2) {
        proc(right_read, right_write, left_read, left_write, des, 0);
    }
    
    fclose(right_read);
    fclose(right_write);
    fclose(left_read);
    fclose(left_write);
    
    int status = 0;
    while ((wait(&status)) > 0);

    printf("Done\n");
    fflush(stdout);
        
}
