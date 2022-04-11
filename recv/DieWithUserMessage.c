#include <stdio.h>
#include <stdlib.h>
#include "Practical.h"

void DieWithUserMessage(const char *msg, const char *details) {
    fputs(msg, stderr);
    fputs(" : ", stderr);
    fputs(details, stderr);
    fputc('\n', stderr);
    exit(1);
}

void DieWithSystemMessage(const char *msg) {
    fputs(msg, stderr);
    exit(1);
}
