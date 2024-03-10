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
    {"HELP\0", &help_command},
    {"CDUP\0", &cdup},
    {"DELE\0", &dele},
    {"NOOP\0", &noop},
    {"CWD\0", &cwd},
    {"PWD\0", &pwd},
    {"NULL\0", NULL}
};

int help_command(server_t *server, int socket)
{
    if (server == NULL)
        return KO;
    if (server_response(socket, "214 Help message.\r\n  USER [arg]:\r\n\
    send ur username to connect\r\n  PASS [arg]:\r\n\
    send ur pass to connect\r\n  CWD [arg]:\r\n\
    moves through server files\r\n  CDUP\r\n\
    moves to the parent file\r\n  PWD [arg]:\r\n\
    is used to give the position in files\r\n  DELE [arg]:\r\n\
    deletes a file on the server\r\n  QUIT:\r\n\
    allows you to disconnect\r\n") == KO)
        return KO;
    return OK;
}

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
