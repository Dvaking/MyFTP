/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** socket_initialization
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "struct.h"
#include "macro.h"

static int client_initialization(server_t *server, char const *path)
{
    if (server == NULL)
        return KO;
    for (int i = 0; i < __FD_SETSIZE; i++){
        server->list[i].socket = i;
        server->list[i].addr_len = sizeof(server->list[i].addr);
        server->list[i].username = 0;
        server->list[i].password = 0;
        server->list[i].is_connected = false;
        server->list[i].path = strdup(path);
        server->list[i].command = NULL;
    }
    return OK;
}

static int socket_initialization_sub(server_t *server)
{
    if (server == NULL)
        return KO;
    if (bind(server->server_socket, (struct sockaddr *)&server->server_addr,
    sizeof(server->server_addr)) == KO) {
        perror("Bind failed");
        return KO;
    }
    if (listen(server->server_socket, 5) == KO) {
        perror("Listen failed");
        return KO;
    }
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

int structure_initialization(server_t *server, char const *const *av)
{
    char *tmp = NULL;

    if (server == NULL || av == NULL)
        return KO;
    tmp = realpath(av[2], NULL);
    server->port = atoi(av[1]);
    if (server->port < 0) {
        perror("Port is not a number");
        return KO;
    }
    if (tmp == NULL) {
        perror("Path is not valid");
        return KO;
    }
    server->server_addr_len = sizeof(server->server_addr);
    if (client_initialization(server, tmp) == KO)
        return KO;
    free(tmp);
    return OK;
}
