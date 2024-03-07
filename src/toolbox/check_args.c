/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** check_args
*/

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "macro.h"

static int arg_error(char const *arg, bool is_arg_value)
{
    if (arg == NULL)
        return KO;
    if (is_arg_value)
        return OK;
    if (strcmp(arg, "port") == 0)
        return OK;
    if (strcmp(arg, "path") == 0)
        return OK;
    if (strcmp(arg, "help") == 0)
        return OK;
    return KO;
}

static int is_digit(char const *arg, bool is_arg_value)
{
    if (arg == NULL)
        return KO;
    if (!is_arg_value)
        return OK;
    for (int i = 0; arg[i] != '\0'; i++){
        if (isdigit(arg[i]) == KO)
            return KO;
    }
    return OK;
}

int check_args(int ac, char const *const *av)
{
    bool is_arg_value = false;

    if (ac < 3 && av == NULL)
        return KO;
    for (int i = 1; av[i] != NULL; i++){
        if (arg_error(av[i], is_arg_value) == KO)
            return KO;
        if (is_digit(av[i], is_arg_value) == KO)
            return KO;
        is_arg_value = !is_arg_value;
    }
    return OK;
}
