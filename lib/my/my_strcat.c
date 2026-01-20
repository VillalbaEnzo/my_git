/*
** EPITECH PROJECT, 2024
** B-CPE-100-LYN-1-1-cpoolday07-jan.nguyen
** File description:
** my_strcat.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_strlen2(char const *str)
{
    int var_lenght = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        var_lenght++;
    }
    return var_lenght;
}

char *my_strcpy2(char *dest, char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        dest[i] = str[i];
    }
    i++;
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, char const *src)
{
    int taille = my_strlen2(dest);

    my_strcpy2(dest + taille, src);
    dest[taille + 1] = '\0';
    return dest;
}
