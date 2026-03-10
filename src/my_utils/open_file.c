/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** open_file
*/

#include "database.h"

FILE *open_file(const char *filename)
{
    FILE *stream = fopen(filename, "r");

    if (!stream) {
        perror("fopen");
        return NULL;
    }
    return stream;
}
