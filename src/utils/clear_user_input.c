/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** clear_user_input.c
*/

#include "my.h"

void clear_user_input(char *input)
{
    if (!input)
        return;
    for (int i = 0; input[i] != '\0'; i++)
        input[i] = '\0';
}
