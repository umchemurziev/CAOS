#include <ctype.h>
#include <dirent.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>  // stat, lstat, fstat
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    DIR * dr = opendir(argv[1]);

    struct dirent *dir_info;
    uint64_t res = 0;

    while ((dir_info = readdir(dr))) {
        char buf[PATH_MAX];
        if (snprintf(buf, sizeof(buf), "%s/%s", argv[1], dir_info->d_name) < sizeof(buf)) {
            struct stat file_info;
            int b = (stat(buf, &file_info) >= 0) ? 1 : 0;
            // if (stat(buf, &file_info) >= 0) {
            //     b = 1;
            // } else {
            //     b = 0;
            // }
            b = (b && S_ISREG(file_info.st_mode)) ? 1 : 0;
            // if (b && S_ISREG(file_info.st_mode)) {
            //     b = 1;
            // } else {
            //     b = 0;
            // }
            b = (b && isupper((unsigned char)dir_info->d_name[0])) ? 1 : 0;
            // if (b && isupper((unsigned char)dir_info->d_name[0])) {
            //     b = 1;
            // } else {
            //     b = 0;
            // }
            b = (b && file_info.st_uid == getuid()) ? 1 : 0;
            // if (b && file_info.st_uid == getuid()) {
            //     b = 1;
            // } else {
            //     b = 0;
            // }
            if (b) {
                res += file_info.st_size;
            }
        }
    }
    printf("%llu\n", res);
    closedir(dr);
}

// Каждое из условий со строк 21-25, 26-30, 31-35, 36-40 можно заменить одним выражением в языке Си
