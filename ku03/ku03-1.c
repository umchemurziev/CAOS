#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

enum {STEP = 9, MOD = 7};


int main(int args, char **argv) {
    int64_t res = 0;
    int ord = 1;

    for (size_t i = 1; i < args; ++i) {
        for (size_t j = 0; argv[i][j]; ++j) {
            res += (argv[i][j] - '0') * ord;
            ord *= STEP;
            res %= MOD;
            ord %= MOD;
        }
    }

    printf("%" PRId64 "\n", res % MOD);
    return 0;
}
