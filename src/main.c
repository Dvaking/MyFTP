/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "proto.h"

int main(int ac, char const *const *av)
{
    if (check_args(ac, av) == KO)
        return 84;
    if (my_ftp(av) == KO)
        return 84;
    return OK;
}
