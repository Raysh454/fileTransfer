#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared/Shared.h"
#include "recv/Receive.h"
#include "send/Send.h"

int main(int argc, char *argv[]) {
    if(argc < 2)
        DieWithUserMessage("cloud", "send/recv");
    
    if(!strcmp(argv[1], "send"))
        cloudSend(argc, argv);
    else if(!strcmp(argv[1], "recv"))
        cloudRecv(argc, argv);
    else
        DieWithUserMessage("cloud", "send/recv");

    return 0;
}
