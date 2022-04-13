#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include "Receive.h"
#include "../shared/Shared.h"

int AcceptTCPConnection(int servSock) {
    struct sockaddr_storage clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);
    
    int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen);
    if(clntSock < 0)
        DieWithSystemMessage("accept() Failed");

    fputc('\n', stdout);
    fputs("Handling client: ", stdout);
    printSocketAddress((struct sockaddr *)&clntAddr, stdout);
    fputc('\n', stdout);

    return clntSock;
}
