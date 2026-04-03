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

static void append_label(data_t *data, label_t *new_label)
{
    label_t *tmp = data->labels;

    if (!new_label)
        return;
    if (!tmp) {
        data->labels = new_label;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_label;
}

static void append_instruction(data_t *data, inst_t *new_inst)
{
    inst_t *tmp = data->inst;

    if (!new_inst)
        return;
    if (!tmp) {
        data->inst = new_inst;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_inst;
}

static void process_line(char *line, data_t *data)
{
    char *c_line = clean_line(line);
    label_t *new_label = NULL;
    inst_t *new_inst = NULL;

    if (!c_line || c_line[0] == '\0')
        return;
    new_label = parse_label(c_line);
    if (new_label) {
        append_label(data, new_label);
        c_line += my_strlen(new_label->name) + 1;
        c_line = clean_line(c_line);
    }
    new_inst = parse_instruction(c_line);
    append_instruction(data, new_inst);
}

void parse_body(FILE *file, data_t *data)
{
    char *line = NULL;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        process_line(line, data);
        free(line);
        line = NULL;
        line = read_line(file, line, false);
    }
}
