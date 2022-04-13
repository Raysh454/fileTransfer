#include<arpa/inet.h>

void DieWithUserMessage(const char *msg, const char *details);
void DieWithSystemMessage(const char *msg);
void printSocketAddress(const struct sockaddr *address, FILE *stream);
int AcceptTCPConnection(int servSock);
void HandleTCPClient(int clientSock, char *storageLocation);
void printFileStatus(char *fName, long fSize, long bytesReceived);
void goAhead(int clientSock);
int setupTCPServer(char* service);
