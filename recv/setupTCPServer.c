#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include "Practical.h"

static const int MAX_PENDING = 5;

int setupTCPServer(char *service) {
    
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_flags = AI_PASSIVE;
    addrCriteria.ai_socktype = SOCK_STREAM;
    addrCriteria.ai_protocol = IPPROTO_TCP;

    struct addrinfo *addrList;
    int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &addrList);
    if(rtnVal != 0)
        DieWithUserMessage("getaddrinfo() Failed", gai_strerror(rtnVal));

    int sock = -1;
    for(struct addrinfo *addr = addrList; addr != NULL; addr = addr->ai_next) {
        sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if(sock < 0)
            continue;

        if(bind(sock, addr->ai_addr, addr->ai_addrlen) == 0 &&
                listen(sock, MAX_PENDING) == 0) {
            struct sockaddr_storage localAddr;
            socklen_t addrSize = sizeof(localAddr);
            if(getsockname(sock, (struct sockaddr *)&localAddr, &addrSize) < 0)
                DieWithSystemMessage("getsockname() Failed");
            fputs("Binding to: ", stdout);
            printSocketAddress((struct sockaddr *)&localAddr, stdout);
            fputc('\n', stdout);
            break;
    }
        close(sock);
        sock = -1;
    }
    freeaddrinfo(addrList);
    return sock;
}

