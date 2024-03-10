/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** pwd
*/

#include <stdlib.h>
#include <string.h>

#include "proto.h"

static char *create_path(char *path, char *msg)
{
    char *tmp = NULL;
    int len_one = 0;
    int len_two = 0;

    if (path == NULL || msg == NULL)
        return NULL;
    len_one = strlen(path);
    len_two = strlen(msg);
    if (len_one == -1 || len_two == -1)
        return NULL;
    tmp = malloc(sizeof(char) * (len_one + len_two + 3));
    if (tmp == NULL)
        return NULL;
    tmp[0] = '\0';
    strcat(tmp, msg);
    strcat(tmp, path);
    strcat(tmp, "\r\n");
    return tmp;
}

int pwd(server_t *server, int socket)
{
    client_t *client;
    char *path;

    if (server == NULL)
        return KO;
    if (is_authenticated(server, socket) == KO)
        return OK;
    client = &server->list[socket];
    if (client->path == NULL)
        return KO;
    path = create_path(client->path, "257 ");
    if (path == NULL)
        return KO;
    if (server_response(socket, path) == KO)
        return KO;
    free(path);
    return OK;
}
