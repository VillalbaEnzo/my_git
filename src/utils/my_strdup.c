/*
** EPITECH PROJECT, 2025
** my_strdup.c
** File description:
** Allocates memory and copies src.
*/
#include "utils.h"
#include <stdlib.h>

char *my_strdup(char *src)
{
    char *new_string = NULL;

    if (src == NULL)
        return NULL;
    new_string = malloc(sizeof(char) * (my_strlen(src) + 1));
    my_strcpy(new_string, src);
    return new_string;
}
