/*
** EPITECH PROJECT, 2023
** proto.h
** File description:
** proto
*/

#ifndef PROTO_H_
    #define PROTO_H_
    #include <stdio.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include "struct.h"
    #include "macro.h"

int my_ftp(char const *const *av);


/* Initialization */
int socket_initialization(server_t *server);
int structure_initialization(server_t *server, char const *const *av);

/* Server */
int server_loop(server_t *server);
int server_response(int socket, char *message);

/* Client */
int client_new_connection(server_t *server);
int is_new_client(server_t *server);
char **client_sending(int socket);
int free_client(server_t *server);

/* Command */
int execute_command(server_t *server, int socket);
int authentification(server_t *server, int socket);
int is_authenticated(client_t *client);
int disconnected(server_t *server, int socket);
int cwd(server_t *server, int socket);
int pwd(server_t *server, int socket);
int cdup(server_t *server, int socket);
int dele(server_t *server, int socket);

/* Toolbox */
int remove_line_break(char *str);
int check_args(int ac, char const *const *av);

#endif /* !PROTO_H_ */
