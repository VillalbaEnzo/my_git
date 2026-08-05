/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** free_array.c
*/

#include "my.h"

void free_array(char **str)
{
    if (!str)
        return;
    for (int i = 0; str[i]; i++)
        free(str[i]);
    free(str);
}
