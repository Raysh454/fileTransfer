#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "Receive.h"
#include "../shared/Shared.h"

long recvFile(int clientSock, long fSize, char *fName, FILE *fp);
long getFileData(int clientSock, char *fName, long *fSize);

void HandleTCPClient(int clientSock, char *storageLocation) {

    char fileName[256];
    long fileSize = 0;
    getFileData(clientSock, fileName, &fileSize);
    char *filePath = malloc(strlen(storageLocation) + strlen(fileName) + 1);
    if(filePath == NULL) {
        puts("malloc() Failed");
        return;
    }
    memcpy(filePath, storageLocation, strlen(storageLocation));
    memcpy(filePath + strlen(storageLocation), fileName, strlen(fileName) + 1);

    goAhead(clientSock);

    FILE *fp = fopen(filePath, "wb");
    if(fp == NULL)
        DieWithSystemMessage("fopen() Failed");
    free(filePath);
    long totalWritten = recvFile(clientSock, fileSize, fileName, fp);
    if(totalWritten != fileSize)
        printf("\nUnexpected number of bytes written to file\nConnection terminated unexpectedly\n");
    else
        printf("\nSuccessfully downloaded file\nTerminating connection\n");
    
    fclose(fp);
    close(clientSock);
}

long recvFile(int clientSock, long fSize, char *fName, FILE *fp) {
    char buffer[BUFSIZ];
    ssize_t numBytesRcvd = recv(clientSock, buffer, BUFSIZ - 1, 0);
    long totalRcvd = numBytesRcvd;

    if(numBytesRcvd < 0)
        DieWithSystemMessage("recv() Failed");

    while(numBytesRcvd > 0) {
        ssize_t numBytesWritten = fwrite(buffer, numBytesRcvd, 1, fp);
        fflush(fp);
        if(numBytesWritten < 0)
            DieWithSystemMessage("fwrite Failed");
        numBytesRcvd = recv(clientSock, buffer, BUFSIZ - 1, 0);
        if(numBytesRcvd < 0)
            DieWithSystemMessage("recv() Failed()");
        totalRcvd += numBytesRcvd;
        printRFileStatus(fName, fSize, totalRcvd);
    }

    return totalRcvd;
}

long getFileData(int clientSock, char *fName, long *fSize) {
    char buffer[BUFSIZ];
    ssize_t numBytesRcvd = recv(clientSock, buffer, BUFSIZ - 1, 0);
    long totalRcvd = numBytesRcvd;

    if(numBytesRcvd < 0)
        DieWithSystemMessage("recv() Failed");

    while(numBytesRcvd > 0) {
        if(buffer[strlen(buffer) - 1] == '$')
            break;
        numBytesRcvd = recv(clientSock, buffer + totalRcvd, BUFSIZ, 0);
        if(numBytesRcvd < 0)
            DieWithSystemMessage("recv() Failed()");
        totalRcvd += numBytesRcvd;
    }
    char strFSize[256];
    for(int i = 0; buffer[i] != ':'; ++i) {
        fName[i] = buffer[i];
        fName[i + 1] = '\0';
    }

    if(buffer[strlen(fName) + 1] == 'U')
        return totalRcvd;

   for(int i = strlen(fName) + 1, k = 0; buffer[i] != '$'; ++i, ++k) {
       strFSize[k] = buffer[i];
       strFSize[k+1] = '\0';
   }
   *fSize = atol(strFSize);

    return totalRcvd;
}
