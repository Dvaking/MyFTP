/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** move_in_folder
*/

#include <string.h>
#include <stdlib.h>

#include "proto.h"

static int get_and_check_the_path(client_t *client, char *path)
{
    char *tmp = NULL;

    if (path == NULL || client == NULL)
        return KO;
    tmp = realpath(path, NULL);
    if (tmp == NULL){
        if (server_response(client->socket, CWD_FAILED) == KO)
            return KO;
        return OK;
    }
    if (chdir(path) == -1) {
        if (server_response(client->socket, CWD_FAILED) == KO)
            return KO;
        return OK;
    }
    client->path = strdup(tmp);
    if (client->path == NULL)
            return KO;
    server_response(client->socket, CWD_SUCCESS);
    return OK;
}

int cwd(server_t *server, int socket)
{
    client_t *client;

    if (server == NULL)
        return KO;
    client = &server->list[socket];
    if (is_authenticated(client) == KO)
        return OK;
    if (client->command[1] == NULL || client->command[1][0] == '\0') {
        if (server_response(socket, CWD_FAILED) == KO)
            return KO;
        return OK;
    }
    if (get_and_check_the_path(client, client->command[1]) == KO) {
        if (server_response(socket, CWD_FAILED) == KO)
            return KO;
    }
    return OK;
}

int cdup(server_t *server, int socket)
{
    client_t *client;

    if (server == NULL)
        return KO;
    client = &server->list[socket];
    if (is_authenticated(client) == KO)
        return OK;
    if (chdir("..") == KO)
        return KO;
    client->path = getcwd(NULL, 0);
    if (client->path == NULL)
        return KO;
    if (server_response(socket, CDUP_SUCCESS) == KO)
        return KO;
    return OK;
}
