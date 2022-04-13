#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Receive.h"
#include "../shared/Shared.h"

int cloudRecv(int argc, char *argv[]) {
    
    if(argc < 4)
        DieWithUserMessage("Parameters: ", "<Host> <File location>");
    
    char *portString = argv[2];
    char *storageLocation = argv[3];

    int servSock = setupTCPServer(portString);
    if(servSock < 0)
        DieWithSystemMessage("setupTCPServer() Failed");

    for(;;) {
        int clntSock = AcceptTCPConnection(servSock);
        HandleTCPClient(clntSock, storageLocation);
        puts("Waiting for connection");
    }
    //Never Reachd
}
