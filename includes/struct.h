/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_
    #include <stdbool.h>
    #include <netinet/in.h>
    #include <sys/select.h>

typedef struct client_s {
    struct sockaddr_in addr;
    socklen_t addr_len;
    int socket;
    int username;
    int password;
    char **command;
    bool is_connected;
} client_t;

typedef struct server_s {
    struct client_s list[FD_SETSIZE];
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;
    int port;
    int server_socket;
    fd_set ready_socket;
    fd_set current_socket;
} server_t;

struct function_tab_s {
    char *str;
    int (*flags)(server_t *server, int socket);
};


#endif /* !STRUCT_H_ */
