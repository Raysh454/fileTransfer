#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "Practical.h"

void waitForGo(int sock) {
    char *goString = "7cea75aef83f0f84a180fc134ce85700d25f6c52bdcfa860481d4bd5824d2d19";
    size_t goStringLen = strlen(goString);
    char buffer[BUFSIZ];
    
    size_t bytesRcvd = recv(sock, buffer, BUFSIZ - 1, 0);

    if(bytesRcvd < 0)
        DieWithSystemMessage("waitForGo() recv() Failed");
    size_t totalRcvd = bytesRcvd;
   
    while(totalRcvd < goStringLen) {
        bytesRcvd = recv(sock, buffer + totalRcvd, BUFSIZ-1, 0);
        
        if(bytesRcvd < 0)
            DieWithSystemMessage("waitForGo() recv() Failed");

        totalRcvd += bytesRcvd;
    }
    if(strcmp(buffer, goString))
            DieWithUserMessage("waitForGo() Failed", "Couldn't Match strings");
}
