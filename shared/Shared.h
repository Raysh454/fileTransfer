#include<arpa/inet.h>

void DieWithUserMessage(const char *msg, const char *details);
void DieWithSystemMessage(const char *msg);
void printSocketAddress(const struct sockaddr *address, FILE *stream);
void goAhead(int clientSock);
void waitForGo(int sock);
