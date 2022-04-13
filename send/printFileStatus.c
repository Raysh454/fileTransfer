#include <stdio.h>
#include "Practical.h"

void printFileStatus(char *fName, long fSize, long bytesSent) {
        if(fSize == -1)
            puts("Unable to get file size");
        else if(fSize < 1024)
            printf("Send: %ld Bytes out of: %ld Bytes\t\tFile: %s\r", bytesSent, fSize, fName);
        else if(fSize > 1024 && fSize < 1048576)
            printf("Send: %ld KB out of: %ld KB\t\tFile: %s\r", bytesSent / 1024, fSize / 1024, fName);
        else if(fSize > 1048576)
            printf("Send: %ld MB out of: %ld MB\t\tFile: %s\r", bytesSent / 1024 / 1024, fSize / 1024 / 1024, fName);
        else
            printf("Send: %ld GB out of: %ld GB\t\tFile: %s\r", bytesSent / 1024 / 1024 / 1024, fSize / 1024 / 1024 / 1024, fName);
    fflush(stdout);
    return;
}
