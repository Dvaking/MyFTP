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

static int struture_initialization(server_t *server, char const *const *av)
{
    if (server == NULL || av == NULL)
        return KO;
    server->port = atoi(av[1]);
    if (server->port == -1) {
        perror("Port is not a number");
        return KO;
    }
    return OK;
}

static int my_ftp_loop(server_t *server)
{
    fd_set current_socket;

    FD_ZERO(&current_socket);
    FD_SET(server->server_socket, &current_socket);
    while (1) {
        server->ready_socket = current_socket;
        printf("Waiting for connection...\n");
        if (select(FD_SETSIZE, &current_socket, NULL, NULL, NULL) == KO) {
            perror("Select failed");
            return KO;
        }
        if (get_information(server) == KO){
            return KO;
        }
    }
    return OK;
}

int my_ftp(char const *const *av)
{
    struct server_s server;

    if (strcmp(av[1], "-help") == 0) {
        if (write_message() == KO)
            return KO;
        return OK;
    }
    if (struture_initialization(&server, av) == KO)
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
