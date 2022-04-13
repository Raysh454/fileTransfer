int cloudRecv(int argc, char *argv[]);
int AcceptTCPConnection(int servSock);
void HandleTCPClient(int clientSock, char *storageLocation);
void printRFileStatus(char *fName, long fSize, long bytesReceived);
int setupTCPServer(char* service);
