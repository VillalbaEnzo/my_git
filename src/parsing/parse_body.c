/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_body.c
*/

#include "op.h"

parse_body(FILE *file)
{
    int counter = 0;
    inst_t *inst = NULL;
    label_t *label = NULL;
    char *line = NULL;

    line = read_line(file, line);
    while (line) {
        
        free(line);
        line = NULL;
        line = read_line(file, line);
    }
}