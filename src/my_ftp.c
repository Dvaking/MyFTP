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

static int write_message(void)
{
    if (write(1, "USAGE: ./my_ftp port path\n\n\
        port  is the port number on which the server socket listens\n\
        path  is the path to the home directory for the Anonymous user\n",
        167) == KO)
            return KO;
    return OK;
}

static int my_ftp_loop(server_t *server)
{
    FD_ZERO(&server->current_socket);
    FD_SET(server->server_socket, &server->current_socket);
    while (1) {
        printf("Waiting for connection\n");
        server->ready_socket = server->current_socket;
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
    if (strcmp(av[1], "-help") == 0) {
        if (write_message() == KO)
            return KO;
        return OK;
    }
    if (structure_initialization(&server, av) == KO)
        return KO;
    if (socket_initialization(&server) == KO)
        return KO;
    if (my_ftp_loop(&server) == KO){
        close(server.server_socket);
        return KO;
    }
    close(server.server_socket);
    return OK;
}
