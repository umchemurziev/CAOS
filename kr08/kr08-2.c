#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main (int argc, char ** argv) {
	unsigned long long ans = 0;
    int des = 0;
    int fdt = 0;
    int sdt = 0;
    
    int right[2] = { 0, 0 };
    int left[2] = { 0, 0 };
    pipe(right);
    pipe(left);

    FILE* wl = fdopen(left[1], "w");
    FILE* rl = fdopen(left[0], "r");
    FILE* wr = fdopen(right[1], "w");
    FILE* rr = fdopen(right[0], "r");
    FILE* f1 = fopen(argv[1], "r");
    FILE* f2 = fopen(argv[2], "r");

    pid_t pid = fork();
    if (!pid) {
        fclose(wr);
        fclose(rl);
        fclose(f2);
        fclose(rr);

        ans = 0;
        des = 0;

        while (fscanf(f1, "%d", &des) > 0) {
            ans += des;
        }
        fprintf(wl, "%d\n", (int)ans);
        fflush(wl);
        
        fclose(wl);
        fclose(f1);
        exit(0);
    }
    
    pid_t pid2 = fork();
    if (!pid2) {
        fclose(wl);
        fclose(rr);
        fclose(rl);
        fclose(f1);

        des = 0;
        ans = 0;

        while (fscanf(f2, "%d", &des) > 0) {
            ans += des;
        }
        fprintf(wr, "%d\n", (int)ans);
        fflush(wr);

        fclose(wr);
        fclose(f2);
        exit(0);
    }
    
    fclose(f1);
    fclose(f2);
    fclose(wr);
    fclose(wl);
    
    waitpid(pid2, NULL, 0);
    fscanf(rr, "%d", &sdt);
    fclose(rr);
    
    waitpid(pid, NULL, 0);
    fscanf(rl, "%d", &fdt);
    fclose(rl);
    
    int32_t out = (int64_t) fdt + sdt;
    printf("%d %d %" PRId32, sdt, fdt, out);
    fflush(stdout);

    return 0;
}
