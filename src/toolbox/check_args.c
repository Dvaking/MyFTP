/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** check_args
*/

#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "macro.h"

static int is_digit(char const *arg)
{
    if (arg == NULL)
        return KO;
    for (int i = 0; arg[i] != '\0'; i++){
        if (isdigit(arg[i]) == OK)
            return KO;
    }
    return OK;
}

static int is_good_path(char const *path)
{
    char *tmp = NULL;

    if (path == NULL)
        return KO;
    tmp = realpath(path, NULL);
    if (tmp == NULL)
        return KO;
    if (access(path, F_OK) == KO)
        return KO;
    free(tmp);
    return OK;
}

static int help_message(char const *str)
{
    if (str == NULL)
        return KO;
    if (strcmp(str, "-help") != 0)
        return OK;
    if (write(1, "USAGE: ./my_ftp port path\n\n\
        port  is the port number on which the server socket listens\n\
        path  is the path to the home directory for the Anonymous user\n",
        167) == KO)
            return KO;
    return OK;
}

int check_args(int ac, char const *const *av)
{
    if (ac < 3 || av == NULL)
        return KO;
    if (strcmp(av[1], "-help") == 0){
        if (help_message(av[1]) == KO)
            return KO;
        return OK;
    }
    if (is_digit(av[1]) == KO)
        return KO;
    if (is_good_path(av[2]) == KO)
        return KO;
    return OK;
}
