/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** get_information
*/

#include <sys/select.h>
#include <unistd.h>

#include "proto.h"

static int wath_type_off_connection(server_t *server, int index)
{
    if (FD_ISSET(index, &server->ready_socket)) {
        if (client_connection(server, index) == KO)
            return KO;
    }
    return OK;
}

int get_information(server_t *server)
{
    if (server == NULL)
        return KO;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (wath_type_off_connection(server, i) == KO)
            return KO;
    }
    return OK;
}
