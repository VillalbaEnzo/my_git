/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_body.c
*/

#include "op.h"

static void clear_com(char *line)
{
    int idx = 0;

    while (line[idx] != '\0' && line[idx] != '#')
        idx++;

    if (line[idx] == '#')
        line[idx] = '\0';
}

// static int find_inst(char *line);

void parse_body(FILE *file)
{
    int counter = 0;
    inst_t *inst = NULL;
    label_t *label = NULL;
    char *line = NULL;

    line = read_line(file, line);
    while (line) {
        clear_com(line);
        free(line);
        line = read_line(file, line);
        printf("%s", line);
    }
}
