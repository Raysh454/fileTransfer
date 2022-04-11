#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Practical.h"

int main(int argc, char *argv[]) {
    
    if(argc != 3)
        DieWithUserMessage("Parameters: ", "<Host> <File location>");
    
    char *portString = argv[1];
    char *storageLocation = argv[2];

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
