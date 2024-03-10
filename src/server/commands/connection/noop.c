/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** noop
*/

#include "proto.h"

int noop(server_t *server, int socket)
{
    if (server == NULL)
        return KO;
    if (is_authenticated(&server->list[socket]) == KO)
        return OK;
    if (server_response(socket, COMMAND_SUCCESS) == KO)
        return KO;
    return OK;
}
