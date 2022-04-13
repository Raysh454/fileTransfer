#include <stdio.h>
#include "Practical.h"

void printFileStatus(char *fName, long fSize, long bytesReceived) {
        if(fSize == -1)
            printf("Received: %ld, Unable to get file size\t\tFile: %s", bytesReceived, fName);
        else if(fSize < 1024)
            printf("Send: %ld Bytes out of: %ld Bytes\t\tFile: %s\r", bytesReceived, fSize, fName);
        else if(fSize > 1024 && fSize < 1048576)
            printf("Send: %ld KB out of: %ld KB\t\tFile: %s\r", bytesReceived / 1024, fSize / 1024, fName);
        else if(fSize > 1048576)
            printf("Send: %ld MB out of: %ld MB\t\tFile: %s\r", bytesReceived / 1024 / 1024, fSize / 1024 / 1024, fName);
        else
            printf("Send: %ld GB out of: %ld GB\t\tFile: %s\r", bytesReceived / 1024 / 1024 / 1024, fSize / 1024 / 1024 / 1024, fName);
    fflush(stdout);
    return;
}
