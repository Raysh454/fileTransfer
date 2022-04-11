#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

long recvFile(int clientSock, long fSize, FILE *fp);
long getFileData(int clientSock, char *fName, long *fSize);

void HandleTCPClient(int clientSock, char *storageLocation) {
    
    char fileName[256];
    long fileSize = 0;
    getFileData(clientSock, fileName, &fileSize);
    char *filePath = strcat(storageLocation, fileName);
    
    if(fileSize == 0)
        printf("Downloading file: %s\nUnable to get file size\n", fileName + 1);
    else
        printf("Downloading file: %s\nSize: %ld MB\n", fileName + 1, fileSize / 1024 / 1024);
    fflush(stdout);

    goAhead(clientSock);

    FILE *fp = fopen(filePath, "wb");
    if(fp == NULL)
        DieWithSystemMessage("fopen() Failed");

    long totalWritten = recvFile(clientSock, fileSize, fp);
    if(totalWritten != fileSize)
        printf("\nUnexpected number of bytes written to file\nTerminating connection\n");
    else
        printf("\nSuccessfully downloaded file\nConnection terminated unexpectedly\n");
    fclose(fp);
    close(clientSock);
}

long recvFile(int clientSock, long fSize, FILE *fp) {
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
        if(fSize == 0)
            printf("\rReceived: %ld MB", totalRcvd / 1024 / 1024);
        else
            printf("\rReceived: %ld MB, out of %ld MB", totalRcvd / 1024 / 1024, fSize / 1024 / 1024);
        fflush(stdout);
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

