/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-48
** File description:
** my_putstr.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_putstr(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 84;
    while (str[i] != '\0')
        i++;
    write(1, str, i);
    return 0;
}

int my_putstr_maj(char const *str)
{
    char buffer[4096];
    int i = 0;

    if (str == NULL)
        return 84;
    while (str[i] != '\0') {
        buffer[i] = (str[i] >= 'a' && str[i] <= 'z') ?
            str[i] - 'a' + 'A' : str[i];
        i++;
        if (i == 4096) {
            write(1, buffer, i);
            i = 0;
        }
    }
    if (i > 0)
        write(1, buffer, i);
    return 0;
}
