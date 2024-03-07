/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_
    #include <netinet/in.h>
    #include <sys/select.h>

typedef struct client_s {
    struct sockaddr_in addr;
    socklen_t addr_len;
    int socket;
    char *username;
    char *password;
} client_t;

typedef struct server_s {
    struct client_s list[FD_SETSIZE];
    struct sockaddr_in server_addr;
    int port;
    int server_socket;
    fd_set ready_socket;
} server_t;

#endif /* !STRUCT_H_ */
