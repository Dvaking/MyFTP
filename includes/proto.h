/*
** EPITECH PROJECT, 2023
** proto.h
** File description:
** proto
*/

#ifndef PROTO_H_
    #define PROTO_H_
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <stdio.h>
    #include <unistd.h>
    #include "struct.h"
    #include "macro.h"

int my_ftp(char const *const *av);

int check_args(int ac, char const *const *av);

int get_information(server_t *server);
int socket_initialization(server_t *server);
int client_connection(server_t *server, int index);

int accept_connection(int server_socket);

#endif /* !PROTO_H_ */
