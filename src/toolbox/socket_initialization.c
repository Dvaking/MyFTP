/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** socket_initialization
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "struct.h"
#include "macro.h"

static int socket_initialization_sub(server_t *server)
{
    if (server == NULL)
        return KO;
    if (bind(server->server_socket, (struct sockaddr *)&server->server_addr,
    sizeof(server->server_addr)) == KO) {
        perror("Bind failed");
        return KO;
    } else
        printf("Bind Success\n");
    printf("Connection from %s:%d\n", IPV4, server->port);
    if (listen(server->server_socket, 5) == KO) {
        perror("Listen failed");
        return KO;
    } else
        printf("Server listenning...\n");
    return OK;
}

int socket_initialization(server_t *server)
{
    if (server == NULL)
        return KO;
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_socket == -1){
        perror("Socket creation failed");
        return KO;
    }
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = inet_addr(IPV4);
    server->server_addr.sin_port = htons(server->port);
    if (socket_initialization_sub(server) == KO)
        return KO;
    return OK;
}
