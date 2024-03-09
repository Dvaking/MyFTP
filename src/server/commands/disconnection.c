/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** disconnection
*/

#include <stdio.h>
#include <string.h>

#include "proto.h"
#include "proto_lib.h"

int disconnected(server_t *server, int socket)
{
    client_t *client;

    if (server == NULL)
        return KO;
    client = &server->list[socket];
    if (client->is_connected == true) {
        if (server_response(socket, CLOSE_CONNECTION) == KO)
            return KO;
        client->username = 0;
        client->password = 0;
        client->is_connected = false;
        FD_CLR(socket, &server->current_socket);
        close(socket);
        printf("Client n°%d disconnected\n", socket);
    }
    return OK;
}
