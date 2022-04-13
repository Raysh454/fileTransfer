void DieWithUserMessage(const char *msg, const char *details);
void DieWithSystemMessage(const char *msg);
void waitForGo(int clientSock);
void printFileStatus(char *fName, long fSize, long bytesSent);
int setupTCPClient(char *address, char* service);
