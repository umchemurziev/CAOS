#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


struct addrinfo *res;
struct addrinfo hints = { };
void reset (void)
{
    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_STREAM;
}

int sch = 0;
FILE * in_file;
FILE * out_file;


void cpn(int num)
{
    int r = 0;
    for (int i = 0; i <= num; ++i)
    {
        r = fprintf(out_file, "%d\n", i);
        fflush(out_file);

        if (r < 0)
        {
            freeaddrinfo(res);
            _exit(0);
        }
    }
}
void cpk(char * key)
{
    int r = fprintf(out_file, "%s\n", key);
    fflush(out_file);

    if (r < 0)
    {
        freeaddrinfo(res);
        _exit(0);
    }

}
int crk()
{
    int num;

    if (fscanf(in_file, "%d", &num) < 0)
    {
        freeaddrinfo(res);
        _exit(0);
    }

    return num;
}

int main(int argc, char ** argv)
{
    if (argc <= 3)
    {
        return 1;
    }
    reset();
    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0)
        _exit(0);

    sch = socket(res->ai_family, res->ai_socktype, 0);

    if (sch < 0)
    {
        freeaddrinfo(res);
        _exit(0);
    }

    if (connect(sch, res->ai_addr, res->ai_addrlen) < 0)
    {
        freeaddrinfo(res);
        _exit(0);
    }
    int sfd2 = dup(sch);

    in_file = fdopen(sch, "r");
    out_file = fdopen(sfd2, "w");
    cpk(argv[3]);

    int num = crk();

    cpn(num);

    unsigned long long ans;

    if (fscanf(in_file, "%llu", &ans) < 0)
    {
        freeaddrinfo(res);
        _exit(0);
    }

    printf("%llu\n", ans);
    fflush(stdout);

    fclose(in_file);
    fclose(out_file);
    freeaddrinfo(res);

    return 0;
}
