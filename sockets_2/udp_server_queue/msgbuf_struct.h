#ifndef __MSGBUFSTRUCT_H
#define __MSGBUFSTRUCT_H

#include <netinet/in.h>

#define MSG_SIZE 80
#define UDP_REQUEST 1

typedef union client_data {
    int fd;
    struct sockaddr_in client;
} client_data_t;

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
    client_data_t data;
};

#endif