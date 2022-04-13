#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include "Send.h"
#include "../shared/Shared.h"

int setupTCPClient(char *address, char *service) {
   
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_socktype = SOCK_STREAM;
    addrCriteria.ai_protocol = IPPROTO_TCP;
    struct addrinfo *addrList;
    
    int rtnVal = getaddrinfo(address, service, &addrCriteria, &addrList);
    if(rtnVal != 0)
        DieWithUserMessage("getaddrinfo() Failed", gai_strerror(rtnVal));
    
    int sock = -1;
    for(struct addrinfo *servAddr = addrList; servAddr != NULL; servAddr = servAddr->ai_next) {
        sock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
        if(sock < 0)
            continue;
        
        if(connect(sock, servAddr->ai_addr, servAddr->ai_addrlen) == 0)
            break;

        close(sock);
        sock = -1;
    }

    freeaddrinfo(addrList);
    return sock;
}
