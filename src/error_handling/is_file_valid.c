/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** is_file_valid
*/
#include <stdlib.h>
#include <stdbool.h>

bool is_file_valid(char *filename)
{
    char *save = NULL;
    bool ret = false;

    if (filename == NULL)
        return ret;
    save = filename;
    while (*(filename + 2) != '\0')
        filename++;
    if (*filename == '.' && *(filename + 1) == 's')
        ret = true;
    filename = save;
    return ret;
}
