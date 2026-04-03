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

    if (!line)
        return;
    while (line[idx] != '\0' && line[idx] != COMMENT_CHAR)
        idx++;
    if (line[idx] == COMMENT_CHAR)
        line[idx] = '\0';
}

void parse_body(FILE *file, data_t *data)
{
    char *line = NULL;
    inst_t *head = NULL;
    inst_t *end = NULL;
    inst_t *new_inst = NULL;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        new_inst = parse_instruction(clean_line(line));
        if (new_inst && !head)
            head = new_inst;
        if (new_inst && end)
            end->next = new_inst;
        if (new_inst)
            end = new_inst;
        free(line);
        line = NULL;
        line = read_line(file, line, false);
    }
    data->inst = head;
}
