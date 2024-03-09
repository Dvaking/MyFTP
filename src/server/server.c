/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** server
*/

#include <sys/select.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int server_response(int socket, char *message)
{
    if (dprintf(socket, message) == KO) {
        perror("Response failed");
        return KO;
    }
    return OK;
}

static int server_connection_type_sub(server_t *server, int socket)
{
    if (socket == server->server_socket){
        if (client_new_connection(server) == KO)
            return KO;
    } else {
        printf("socket n°%d\n", socket);
        if (execute_command(server, socket) == KO)
            return KO;
    }
    return OK;
}

static int server_connection_type(server_t *server, int socket)
{
    if (FD_ISSET(socket, &server->ready_socket)) {
        if (server_connection_type_sub(server, socket) == KO)
            return KO;
    }
    return OK;
}

int server_loop(server_t *server)
{
    if (server == NULL)
        return KO;
    for (int i = 0; i < __FD_SETSIZE; i++) {
        if (server_connection_type(server, i) == KO)
            return KO;
    }
    return OK;
}
