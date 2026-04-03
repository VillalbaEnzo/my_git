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

static label_t *append_label(data_t *data, label_t *new_label)
{
    label_t *head = NULL;
    label_t *end = NULL;

    if (new_label && !head)
        head = new_label;
    if (new_label && end)
        end->next = new_label;
    if (new_label)
        end = new_label;
        return head;
}

static inst_t *append_instruction(data_t *data, inst_t *new_inst)
{
    inst_t *head = NULL;
    inst_t *end = NULL;

    if (new_inst && !head)
        head = new_inst;
    if (new_inst && end)
        end->next = new_inst;
    if (new_inst)
        end = new_inst;
        return head;
}

void parse_body(FILE *file, data_t *data)
{
    char *line = NULL;
    label_t *new_label = NULL;
    label_t *head_lab = NULL;
    inst_t *new_inst = NULL;
    inst_t *head_inst = NULL;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        new_label = parse_label(clean_line(line));
        new_inst = parse_instruction(clean_line(line));
        head_lab = append_label(data, new_label);
        head_inst = append_instruction(data, new_inst);
        free(line);
        line = NULL;
        line = read_line(file, line, false);
    }
    data->inst = head_inst;
    data->labels = head_lab;
}
