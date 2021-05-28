#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>




int main() {
    enum { BUF_SIZE = 1001 };
    char host[BUF_SIZE];
    char service[BUF_SIZE];

    struct addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    void reset(void)
    {
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
    }
    reset();
    while (scanf("%1000s %1000s", host, service) != EOF)
    {
        reset();
        struct addrinfo *info;
        int err = getaddrinfo(host, service, &hints, &info);
        if (err != 0)
        {
            printf("%s\n", gai_strerror(err));
            fflush(stdout);
        }
        else if (err == 0)
        {
            struct sockaddr_in* min_addr = NULL;
            while (info != NULL)
            {
                struct sockaddr_in *cur_sock = (struct sockaddr_in *) info->ai_addr;
                if (min_addr == NULL || ntohl(min_addr->sin_addr.s_addr) >= ntohl(cur_sock->sin_addr.s_addr))
                    min_addr = cur_sock;
                info = info->ai_next;
            }
            printf("%s:%hu\n", inet_ntoa(min_addr->sin_addr), ntohs(min_addr->sin_port));
            fflush(stdout);
            freeaddrinfo(info);
        }
    }
    return 0;
}
