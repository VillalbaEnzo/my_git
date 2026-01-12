/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strstr.c
*/

#include "../includes/my.h"
#include "unistd.h"

char *my_strstr(char *str, char *to_find)
{
    int i;
    int j;

    if (str == NULL || to_find == NULL || to_find[0] == '\0')
        return str;
    for (i = 0; str[i] != '\0'; i++) {
        j = 0;
        while (str[i + j] == to_find[j] && to_find[j] != '\0')
            j++;
        if (to_find[j] == '\0')
            return &str[i];
    }
    return 0;
}
