#include <stdio.h>
#include <time.h>
#include <inttypes.h>

enum { HD = 24, SH = 3600, DS = HD * SH };

int main() {
    int32_t inp;
    while(scanf("%" SCNd32, &inp) == 1) {
        int32_t sc;
        time_t res;
        time_t curtime = time(NULL);
        if (__builtin_add_overflow(sc, curtime, &res) || __builtin_mul_overflow(DS, inp, &sc)) {
            printf("OVERFLOW\n");
        }
        else {
            char data[228];
            struct tm *Time = localtime(&res);
            strftime(data, sizeof(data), "%Y-%m-%d", Time);
            printf("%s\n", data);
        }
    }
}
