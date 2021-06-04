#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { SZ = 4 };


int main (int argc, char * argv[]){
    long long x = 0;
    long ans = 0;
    for (int i = 1; i < argc; ++i) {
        x = strtoll(argv[i], NULL, 10);
        ans = 0;
        if (!fork())
        {
            while (x != 0)
            {
                if (x < 0)
                {
                    ans += (-1) * (x % SZ);
                }
                else
                {
                    ans += x % SZ;
                }
                x /= SZ;
            }
            printf("%ld\n", ans);
            fflush(stdout);
            return 0;
        }
        int status = 0;
        while(wait(&status) > 0);
    }
    return 0;
}
