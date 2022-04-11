#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "Practical.h"

void goAhead(int clientSock) {
    char *goString = "7cea75aef83f0f84a180fc134ce85700d25f6c52bdcfa860481d4bd5824d2d19";
    size_t goStringLen = strlen(goString);

    size_t bytesSent = send(clientSock, goString, goStringLen, 0);

    if(bytesSent < 0)
        DieWithUserMessage("goAhead()", "send() Failed");
    else if(bytesSent != goStringLen)
        DieWithUserMessage("goAhead() send() Failed", "Unexpected number of bytes sent");
}
