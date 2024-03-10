/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** athentification
*/

#include <stdio.h>
#include <string.h>

#include "proto.h"
#include "proto_lib.h"

static int is_user(client_t *client, char **command)
{
    if (command == NULL || client == NULL)
        return KO;
    if (strcmp(command[0], "USER") == 0){
        if (command[1] == NULL)
            client->username = KO;
        if (strcmp(command[1], "Anonymous") == 0)
            client->username = 1;
        else
            client->username = KO;
        if (server_response(client->socket, USER_AUTH) == KO)
            return KO;
    }
    return OK;
}

static int is_password(client_t *client, char **command)
{
    int len_str = 0;

    if (command == NULL || client == NULL)
        return KO;
    if (client->username == 0){
        if (server_response(client->socket, NO_USER) == KO)
            return KO;
    }
    if (command[1] != NULL)
        len_str = strlen(command[1]);
    if (len_str == -1)
        return KO;
    if (strcmp(command[0], "PASS") == 0){
        if (command[1] == NULL || len_str == 0) {
            client->password = 1;
        } else {
            client->password = KO;
        }
    }
    return OK;
}

static int check_authentified(client_t *client)
{
    if (client == NULL)
        return KO;
    if (client->password == 0 || client->username == 0)
        return OK;
    if (client->username == 1 && client->password == 1){
        client->is_connected = true;
        if (server_response(client->socket, USER_LOGGED) == KO)
            return KO;
    }
    if (client->username == KO || client->password == KO){
        if (server_response(client->socket, WRONG_ID) == KO)
            return KO;
        client->username = 0;
        client->password = 0;
    }
    return OK;
}

int authentification(server_t *server, int socket)
{
    client_t *client;

    if (server == NULL)
        return KO;
    client = &server->list[socket];
    if (client->is_connected == true){
        if (server_response(client->socket, USER_ALREADY_LOGGED) == KO)
            return KO;
    }
    if (is_user(client, client->command) == KO)
        return KO;
    if (is_password(client, client->command) == KO)
        return KO;
    if (check_authentified(client) == KO)
        return KO;
    return OK;
}

int is_authenticated(client_t *client)
{
    if (client == NULL)
        return KO;
    if (client->is_connected == false){
        if (server_response(client->socket, USER_NOT_LOGGED) == KO)
            return KO;
        return KO;
    }
    return OK;
}
