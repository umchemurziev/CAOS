#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = 0;
    int c = 1;
    char path[PATH_MAX];
    char *dir = getenv("XDG_RUNTIME_DIR");
    
    if (argc <= 1) {
        return 1;
    }

    if (!dir) {
        dir = getenv("TMPDIR");
        if (!dir) {
            strcpy(path, "/tmp");
        } else {
            strcpy(path, dir);
        }
    }

    strcat(path, "/temp.py");

    if (!fd) {
        fd = creat(path, 0700);
        dprintf(fd, "#!/usr/bin/env python3\nimport sys\nprint(");
    }

    for (int i = 1; i < argc - 1; ++i) {
        dprintf(fd, argv[c]);
        dprintf(fd, " * ");
        ++c;
    }
    dprintf(fd, argv[c]);
    dprintf(fd, ")\n");


    close(fd);
    execlp("/bin/sh", "sh", "-c", path, NULL);
}
