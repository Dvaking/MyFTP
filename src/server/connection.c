/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** connection
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "struct.h"
#include "macro.h"

static int connection_response(client_t *client)
{
    if (write(client->socket, "220\n", 4) == KO) {
        perror("Write failed");
        return KO;
    }
    return OK;
}

int accept_connection(server_t *server, client_t *client)
{
    client->socket = 0;
    client->addr_len = sizeof(client->addr);
    client->socket = accept(server->server_socket,
    (struct sockaddr *)&client->addr, &client->addr_len);
    if (client->socket == KO) {
        perror("Accept failed");
        return KO;
    }
    printf("Accepted connection from %s:%d on client socket n°%d\n",
    inet_ntoa(client->addr.sin_addr), ntohs(client->addr.sin_port),
    client->socket);
    if (connection_response(client) == KO)
        return KO;
    return OK;
}

int client_connection(server_t *server, int index)
{
    if (index == server->server_socket) {
        if (accept_connection(server, &server->list[index]) == KO)
            return KO;
        FD_SET(server->list[index].socket, &server->ready_socket);
    }
    return OK;
}
