/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** handle_label.c
*/

#include "op.h"

static label_t *find_label(data_t *data, char *name)
{
    label_t *temp = data->labels;

    while (temp->next) {
        if (my_strcmp(name, temp->name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void handle_label(data_t *data)
{
    inst_t *t_inst = data->inst;
    label_t *t_label = NULL;

    while (t_inst->next) {
        if (!t_inst->args->type == T_LAB)
            t_inst = t_inst->next;
        t_label = find_label(data, t_inst->args->label);
        t_inst->args->distance = t_label->pos - t_inst->pos;
        t_inst = t_inst->next;
    }
}
