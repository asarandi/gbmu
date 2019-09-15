#ifndef TCP_H
# define TCP_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/errno.h>

#define                     SOCKET_DEBUG    true

#define sock_created        1
#define sock_connected      2
#define sock_data_sent      4
#define sock_data_received  8

typedef struct  s_server {
    int                     status;
    int                     server_opt;
    int                     server_sock;
    int                     server_sock_flags;
    struct sockaddr_in      server_address;
    int                     client_sock;
    int                     client_sock_flags;
    int                     client_address_len;
    bool                    is_blocking;
    struct sockaddr_in      client_address;
}   t_server;

typedef struct  s_client {
    int                     status;
    int                     sock;
    int                     sock_flags;
    bool                    is_blocking;
    fd_set                  fdset;    
    struct timeval          tv;    
    struct sockaddr_in      server_address;
}   t_client;

bool    client_create(char *network_address, int network_port);
bool    client_connect();
bool    client_send();
bool    client_recv();
bool    server_create(char *network_address, int network_port);
bool    server_accept();
bool    server_send();
bool    server_recv();

t_client    client;
t_server    server;

#endif
