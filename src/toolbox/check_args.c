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

int check_args(int ac, char const *const *av)
{
    if (ac < 3 || av == NULL)
        return KO;
    if (strcmp(av[1], "-help") == 0)
        return OK;
    if (is_digit(av[1]) == KO)
        return KO;
    return OK;
}
