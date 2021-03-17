#include <stdio.h>
#include <inttypes.h>

int main() {
    int64_t a = 0;
    int64_t a2 = 0;
    int64_t b = 0;
    int64_t b2 = 0;
    int64_t c = 0;
    int64_t c1 = 0;
    int64_t c2 = 0;
    char ch = '0';
    while (ch != EOF) {
        a = 0;
        a2 = 0;
        b = 0;
        b2 = 0;
        c = 0;
        c1 = 0;
        c2 = 0;
        int sign = 0;
        scanf("%" SCNd64 "." "%9" SCNd64, &a, &a2);
        if (a2 % 10 == 5) {
            int64_t NEED_C = 1;
            char ch = '0';
            while (ch != ' ' && ch != EOF && ch != '\n') {
                ch = getchar();
                if (ch != '0' && ch != ' ' && NEED_C && ch != EOF && ch != '\n') {
                    NEED_C = 0;
                    a2 = a2 / 10 + 1;
                }
            }
            if (NEED_C && a2 > 99999999) {
                a2 = a2 / 10;
                if (a2 % 2 != 0) a2 += 1;
            }
        } else if (a2 > 99999999) {
            if (a2 % 10 > 5) {
                a2 /= 10;
                a2 += 1;
            } else if (a2 % 10 < 5) {
                a2 /= 10;
            }
            char ch = '0';
            while (ch != ' ' && ch != EOF && ch != '\n') {
                ch = getchar();
            }
        }
        int64_t a2t = a2;
        while (a2t % 10 == 0 && a2t) {
            a2t /= 10;
        }
        if (a2t == 1) {
            a2 = 0;
            a += 1;
        }
        scanf("%" SCNd64 "." "%9" SCNd64, &b, &b2);
        if (b2 % 10 == 5) {
            int64_t NEED_C = 1;
            char ch = '0';
            while (ch != ' ' && ch != EOF && ch != '\n') {
                ch = getchar();
                if (ch != '0' && ch != ' ' && NEED_C && ch != EOF && ch != '\n') {
                    NEED_C = 0;
                    b2 = b2 / 10 + 1;
                }
            }
            if (NEED_C && b2 > 99999999) {
                b2 = b2 / 10;
                if (b2 % 2 != 0) b2 += 1;
            }
        } else if (b2 > 99999999) {
            if (b2 % 10 > 5) {
                b2 /= 10;
                b2 += 1;
            } else if (b2 % 10 < 5) {
                b2 /= 10;
            }
            char ch = '0';
            while (ch != ' ' && ch != EOF && ch != '\n') {
                ch = getchar();
            }
        }
        int64_t b2t = b2;
        while (b2t % 10 == 0 && b2t) {
            b2t /= 10;
        }
        if (b2t == 1) {
            b2 = 0;
            b += 1;
        }
        while (ch != '\n') {
            ch = getchar();
            if (ch == EOF) break; // lfskjalfdkjsa;fhjl;skjf
        }


        if (a < 0 && b >= 0) {
            a *= -1;
            sign = 1;
        } else if (b < 0 && a >= 0) {
            b *= -1;
            sign = 1;
        } else if (a < 0 && b < 0) {
            a *= -1;
            b *= -1;
        }

        if ((a > 9999999999 && ch != EOF) || (b > 9999999999 && ch != EOF)) {
            printf("%s" "\n", "ERROR");
            continue;
        }

        int64_t a2cp = a2;
        int64_t b2cp = b2;
        while (a2cp) {
            a *= 10;
            a2cp = a2cp / 10;
            c1 += 1;
        }
        a += a2;
        while (b2cp) {
            b *= 10;
            b2cp = b2cp / 10;
            c2 += 1;
        }
        b += b2;
        if (c1 > c2) {
            c = c1;
        } else {
            c = c2;
        }
        while (c1 < c) {
            a *= 10;
            c1 += 1;
        }
        while (c2 < c) {
            b *= 10;
            c2 += 1;
        }

        if (b == 0 && ch != EOF) {
            printf("%s" "\n", "ERROR");
            continue;
        }



        int64_t res = a / b;
        int64_t rs = a / b;
        int64_t res2 = 0;
        int64_t rem = a % b;
        for (size_t i = 0; i < 7; ++i) {
            int64_t j = -1;
            while (rem < b && rem) {
                rem *= 10;
                ++j;
            }
            while (j > 0) {
                res2 *= 10;
                --j;
                ++i;
                if (i >= 7) break;
            }
            res = rem / b;
            rem = rem % b;
            res2 = res2 * 10 + res;
        }

        int64_t end = 0;
        for (size_t i = 0; i < 2; ++i) {
            int64_t j = -1;
            while (rem < b && rem) {
                rem *= 10;
                ++j;
            }
            while (j > 0) {
                end = end * 10;
                --j;
                ++i;
                if (i >= 2) break;
            }
            res = rem / b;
            rem = rem % b;
            end = end * 10 + res;
        }
        res2 = res2 * 100 + end;
        int64_t res2t = res2;

        if (res2 % 10 == 5) {
            int64_t NEED_C = 1;
            if (rem) {
                NEED_C = 0;
                res2 = res2 / 10 + 1;
            }
            if (NEED_C) {
                res2 = res2 / 10;
                if (res2 % 2 != 0) res2 += 1;
            }
        } else if (res2 > 99999999) {
            if (res2 % 10 > 5) {
                res2 /= 10;
                res2 += 1;
            } else if (res2 % 10 < 5) {
                res2 /= 10;
            }
        }
        while (res2t % 10 == 0 && res2t) {
            res2t /= 10;
        }
        if (res2t == 1) {
            res2 = 0;
            rs += 1;
        }

        if (((ch != EOF) && (rs > 9999999999)) || ((rs == 9999999999 && res2 > 99999999) && ch != EOF)) {
            printf("%s" "\n", "ERROR");
            continue;
        }
        if (sign) {
            rs *= -1;
        }
        printf("%" PRId64, rs);
        printf("%c", '.');
        if (res2 == 0) {
            printf("%s", "00000000");
        } else {
            printf("%" PRId64, res2);
        }
        printf("\n");
    }
    return 0;
}

