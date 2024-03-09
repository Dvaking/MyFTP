/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** command
*/


#include <string.h>
#include <stdbool.h>

#include "proto.h"
#include "proto_lib.h"


const struct function_tab_s OPERATORS_FUNCS[] = {
    {"USER\0", &authentification},
    {"PASS\0", &authentification},
    {"QUIT\0", &disconnected},
    {"NULL\0", NULL}
};

static int execute_command_sub(server_t *server, int socket,
    int j, bool *is_exist)
{
    if (server == NULL || is_exist == NULL)
        return KO;
    if (strcmp(OPERATORS_FUNCS[j].str,
    server->list[socket].command[0]) == 0) {
        *is_exist = true;
        if (OPERATORS_FUNCS[j].flags(server, socket) == KO)
            return KO;
    }
    return OK;
}

int execute_command(server_t *server, int socket)
{
    bool is_exist = false;

    if (server == NULL)
        return OK;
    server->list[socket].command = client_sending(socket);
    if (server->list[socket].command == NULL)
        return KO;
    for (int j = 0; strcmp(OPERATORS_FUNCS[j].str, "NULL") != 0; j++) {
        if (execute_command_sub(server, socket, j, &is_exist) == KO)
            return KO;
    }
    if (is_exist == false) {
        if (server_response(socket, UNKNOWN_COMMAND) == KO)
            return KO;
    }
    if (server->list[socket].command != NULL) {
        free_tab(&server->list[socket].command);
        server->list[socket].command = NULL;
    }
    return OK;
}
