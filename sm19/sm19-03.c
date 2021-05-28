#include <arpa/inet.h>
#include <inttypes.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


enum { LS = 5 };

struct sockaddr_in addr = { };

int main(int argc, char **argv) {
    int wrk = 1;
    int val = 1;
    int32_t res = 0;
    int32_t sc = 1;
    int nfd = 0;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) _exit(0);


    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    if (listen(fd, LS) < 0)  _exit(0);
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)  _exit(0);



    while (wrk) {
        int sz = sizeof(addr);
        nfd = accept(fd, (struct sockaddr *) &addr, (socklen_t *) &sz);

        if (nfd < 0)  _exit(0);

        read(nfd, &sc, sizeof(sc));

        close(nfd);
        sc = ntohl(sc);
        wrk = sc;

        res = res + sc;
    }

    printf("%" PRId32, res);
    printf("\n");
    fflush(stdout);

    close(fd);
    return 0;
}