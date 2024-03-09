/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** remove_line_break
*/

#include <stdlib.h>
#include <string.h>

#include "macro.h"

int remove_line_break(char *str)
{
    int i = 0;

    if (str == NULL)
        return KO;
    for (i = 0; str[i] != '\n'; i++) {
        if (str[i] == '\r')
            str[i] = '\0';
    }
    str[i] = '\0';
    return OK;
}
