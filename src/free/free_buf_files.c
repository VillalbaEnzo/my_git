/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5 [WSL: Ubuntu-24.04]
** File description:
** free_buf_files.c
*/

#include "my.h"
#include "struct.h"

void free_buf_files(char **buf)
{
    for (int i = 0; buf[i]; i++)
        free(buf[i]);
    free(buf);
    return;
}
