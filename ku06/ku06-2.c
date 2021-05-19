#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef u_int8_t uint8_t;

int main(int argc, const char *argv[]) {
    int in_fd = open(argv[1], O_RDONLY);
    int out_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0600);
    int64_t mod = strtol(argv[3], NULL, 10);

    uint8_t val = 0;
    int64_t res = 0;
    int64_t order = 1;

    while (read(in_fd, &val, sizeof(val)) > 0) {
        for (size_t i = 0; i < 8; ++i, ++order) {
            int64_t sqrt = (order % mod) * (order % mod);
            sqrt %= mod;
            res += sqrt;
            res %= mod;

            if (((val >> i) % 2) != 0) {
                int32_t final_res = res % mod;
                write(out_fd, &final_res, 4);
            }
        }
    }

    close(in_fd);
    close(out_fd);
}
