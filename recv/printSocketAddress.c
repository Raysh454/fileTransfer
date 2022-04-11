#include<stdio.h>
#include<arpa/inet.h>
#include "Practical.h"

void printSocketAddress(const struct sockaddr *address, FILE *stream) {
    if(address == NULL || stream == NULL)
        return;

    void *numericAddress;
    char addrBuffer[INET6_ADDRSTRLEN];
    in_port_t port;

    switch(address->sa_family) {
        case AF_INET:
            numericAddress = &((struct sockaddr_in *)address)->sin_addr;
            port = ntohs(((struct sockaddr_in *)address)->sin_port);
            break;
        case AF_INET6:
            numericAddress = &((struct sockaddr_in *)address)->sin_addr;
            port = ntohs(((struct sockaddr_in *)address)->sin_port);
            break;
        default:
            fputs("Unknow type", stream);
            return;
    }

    if(inet_ntop(address->sa_family, numericAddress, addrBuffer, sizeof(addrBuffer)) == NULL)
        fputs("Invalid address", stream);
    else {
        fprintf(stream, "%s", addrBuffer);
        if (port != 0)
            fprintf(stream, "-%u", port);
    }
    
    return;
}
