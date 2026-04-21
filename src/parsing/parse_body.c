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

static void process_inst(int *counter, inst_t *new_inst, data_t *data)
{
    new_inst->pos = *counter;
    *counter += new_inst->total;
    append_instruction(data, new_inst);
}

static void process_line(char *line, data_t *data, int *counter)
{
    char *c_line = clean_line(line);
    label_t *new_label = NULL;
    inst_t *new_inst = NULL;

    if (!c_line || c_line[0] == '\0')
        return;
    new_label = parse_label(c_line);
    if (new_label) {
        new_label->pos = *counter;
        append_label(data, new_label);
        c_line += my_strlen(new_label->name) + 1;
        c_line = clean_line(c_line);
    }
    if (c_line[0] != '\0') {
        new_inst = parse_instruction(c_line);
        if (new_inst)
            process_inst(counter, new_inst, data);
        else
            data->error = true;
    }
}

void parse_body(FILE *file, data_t *data)
{
    char *line = NULL;
    int counter = 0;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        process_line(line, data, &counter);
        free(line);
        line = NULL;
        line = read_line(file, line, false);
    }
    data->header->prog_size = counter;
}
