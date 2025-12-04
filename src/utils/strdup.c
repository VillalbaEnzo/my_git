/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** strdup.c
*/

#include "../../include/my.h"

char *my_strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);

    if (dup != NULL)
        strcpy(dup, c);
    return dup;
}

char *my_strndup(const char *c, int n)
{
    int len = 0;
    char *dup;
    int i;

    while (c[len] && len < n)
        len++;
    dup = malloc(len + 1);
    if (dup != NULL) {
        i = 0;
        while (i < len) {
            dup[i] = c[i];
            i++;
        }
        dup[len] = '\0';
    }
    return dup;
}
