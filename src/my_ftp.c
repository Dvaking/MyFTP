/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** my_ftp
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto.h"

static int my_ftp_loop(server_t *server)
{
    FD_ZERO(&server->current_socket);
    FD_SET(server->server_socket, &server->current_socket);
    while (1) {
        server->ready_socket = server->current_socket;
        printf("Waiting for connection...\n");
        if (is_new_client(server) == KO)
            return KO;
        if (server_loop(server) == KO){
            return KO;
        }
    }
    return OK;
}

int my_ftp(char const *const *av)
{
    struct server_s server;

    if (av == NULL)
        return KO;
    if (structure_initialization(&server, av) == KO)
        return KO;
    if (socket_initialization(&server) == KO){
        free_client(&server);
        return KO;
    }
  
    free_client(&server);
    close(server.server_socket);
    return OK;
}
