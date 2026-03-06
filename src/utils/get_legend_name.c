/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** get_legend_name.c
*/

#include "my.h"

char *get_legend_name(char *user_input)
{
    char *name = malloc(sizeof(char) * (strlen(user_input) + 8));

    if (name == NULL)
        return NULL;
    strcpy(name, user_input);
    strcat(name, ".legend");
    return name;
}
