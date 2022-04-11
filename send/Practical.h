void DieWithUserMessage(const char *msg, const char *details);
void DieWithSystemMessage(const char *msg);
void waitForGo(int clientSock);
int setupTCPClient(char *address, char* service);
