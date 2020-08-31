#include <stdlib.h>
#include <stdio.h>

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#include "dbg.h"
#include "lcthw.h"

struct tagbstring NL = bsStatic("\n");
struct tagbstring CLRF = bsStatic("\r\n");

int nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    check(flags >= 0, "Invalid flags in nonblock")

    int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    check(rc == 0, "Can't set nonvblocking");

    return 0;
    error:
    return -1;
}

int client_connect(char *host, char *port)
{
    int rc = 0;
    struct addrinfo *addr = NULL;

    rc  = getaddrinfo(host, port, NULL, &addr);
    check(rc == 0, "Failed to lookup %s:%s", host, port)

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    check(sock >= 0, "Cannot create a socket")

    rc = connect(sock, addr->ai_addr, addr->ai_addrlen);
    check(sock >= 0, "Connect failed")

    rc = nonblock(sock);
    check(rc == 0, "Can't set nonblocking")

    freeaddrinfo(addr);
    return sock;

    error:
    freeaddrinfo(addr);
    return -1;
}

int main()
{
    return 0;
}
