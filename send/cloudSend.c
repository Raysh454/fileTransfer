#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Send.h"
#include "../shared/Shared.h"

ssize_t sendFileData(int sock, char *data, size_t size);
long sendFile(int sock, long fSize, char *fName, FILE *fp);
long fileSize(FILE *fp);

int cloudSend(int argc, char *argv[]) {

    if(argc < 4)
        DieWithUserMessage("Parameters: ", "<host> <service> <file>");

    char *addrString = argv[2];
    char *portString = argv[3];

    for(int i = 4; i < argc; ++i) {
        char *filePath = argv[i];
        char *fileName = strrchr(filePath, '/');
        if(fileName == 0)
            fileName = filePath;

        int sock = setupTCPClient(addrString, portString);
        if(sock < 0)
            DieWithSystemMessage("setupTCPClient() failed");

        FILE *fp = fopen(filePath, "rb");
        if(fp == NULL)
            DieWithSystemMessage("fopen() failed");

        char *seperator = ":";

        sendFileData(sock, fileName, strlen(fileName));
        sendFileData(sock, seperator, strlen(seperator));

        char *sizeError = "Unable to get file size";
        long fSize = fileSize(fp);
        if(fSize == -1) {
            sendFileData(sock, sizeError, strlen(sizeError));
        }else {
            int length = snprintf(NULL, 0,"%ld",fSize);
            char *cfSize = malloc((length+1)*sizeof(char));
            if(cfSize == NULL)
                DieWithUserMessage("malloc()", "Failed to allocate memory for cfSize");
            sprintf(cfSize, "%ld", fSize);
            sendFileData(sock, cfSize, strlen(cfSize));
            free(cfSize);
        }
        sendFileData(sock, "$", 2);
        waitForGo(sock);

        sendFile(sock, fSize, fileName, fp);
        fclose(fp);
        close(sock);
    }
    return 0;
}

long sendFile(int sock, long fSize, char *fName, FILE *fp) {
    char buffer[BUFSIZ];
    size_t bytesRead;
    size_t bytesWritten;
    long totalBytes = 0;
    while((bytesRead = fread(buffer, 1, BUFSIZ, fp)) > 0) {
        bytesWritten = sendFileData(sock, buffer, bytesRead);
        totalBytes += bytesWritten;
        printSFileStatus(fName, fSize, totalBytes);        
    }
    putchar('\n');
    return totalBytes;
}

ssize_t sendFileData(int sock, char *data, size_t size) {
    ssize_t bytesSent = send(sock, data, size, 0);
    if(bytesSent < 0)
        DieWithSystemMessage("\nsendFileData() Failed");
    else if(bytesSent != size)
        DieWithUserMessage("\nsendFileData() Failed", "Unexpected number of bytes sent");
    return bytesSent;
}

long fileSize(FILE *fp){
    long prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}
