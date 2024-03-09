/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** client
*/

#include <stdio.h>

#include "proto.h"
#include "proto_lib.h"

int client_new_connection(server_t *server)
{
    int client_socket = 0;

    client_socket = accept(server->server_socket,
    (struct sockaddr *)&server->server_addr, &server->server_addr_len);
    if (client_socket == KO) {
        perror("Accept failed");
        return KO;
    }
    server->list[client_socket].socket = client_socket;
    printf("Accepted connection on client socket n°%d\n", client_socket);
    FD_SET(client_socket, &server->current_socket);
    if (server_response(client_socket, NEW_CONNECTION) == KO)
        return KO;
    return OK;
}

int is_new_client(server_t *server)
{
    fd_set write_socket;
    fd_set expect_socket;
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&write_socket);
    FD_ZERO(&expect_socket);
    if (select(__FD_SETSIZE, &server->ready_socket, &write_socket,
        &expect_socket, &tv) == KO) {
            perror("Select failed");
            return KO;
        }
    return OK;
}

char **client_sending(int socket)
{
    char buffer[BUFFER_SIZE];
    int pos = 0;
    ssize_t read_size = 0;

    read_size = read(socket, buffer + pos, sizeof(buffer) -
        pos - 1);
    while (read_size > 0) {
        pos += read_size;
        if (pos > BUFFER_SIZE - 1 || buffer[pos - 1] == '\n')
            break;
        read_size = read(socket, buffer + pos, sizeof(buffer) -
            pos - 1);
    }
    if (read_size == -1)
        return NULL;
    if (read_size == 0)
        return NULL;
    remove_line_break(buffer);
    printf("Received: '%s'\n", buffer);
    return my_splitstr(buffer, ' ');
}
