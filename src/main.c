/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>

#include "proto.h"

int main(int ac, char const *const *av)
{
    if (check_args(ac, av) == KO)
        return 84;
    if (strcmp(av[1], "-help") == OK)
        return OK;
    if (my_ftp(av) == KO)
        return 84;
    return OK;
}
