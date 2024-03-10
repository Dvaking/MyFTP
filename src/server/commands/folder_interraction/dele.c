/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** dele
*/

#include <stdlib.h>

#include "proto.h"

int dele(server_t *server, int socket)
{
    client_t *client;

    if (server == NULL)
        return KO;
    client = &server->list[socket];
    if (is_authenticated(client) == KO)
        return OK;
    if (client->command[1] == NULL){
        if (server_response(socket, WRONG_ARGUMENT) == KO)
            return KO;
        return OK;
    }
    if (remove(client->command[1]) == -1){
        if (server_response(socket, WRONG_ARGUMENT) == KO)
            return KO;
        return OK;
    }
    if (server_response(socket, DELETE_SUCCESS) == KO)
        return KO;
    return OK;
}
