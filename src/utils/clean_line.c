/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** clean_line.c
*/

#include "op.h"

/**
 * Clean up a line by removing tabs and spaces at the beginning.
 * @param line line to clean
 * @return char*
 */
char *clean_line(char *line)
{
    int idx = 0;

    while (line[idx] == '\t' || line[idx] == ' ')
        idx++;
    return line + idx;
}
