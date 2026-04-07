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

    while (temp) {
        if (my_strcmp(name, temp->name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

static void calc_arg_dist(data_t *data, inst_t *inst, label_t *label, int i)
{
    if (inst->args[i].label) {
        label = find_label(data, inst->args[i].label);
        if (label)
            inst->args[i].distance = label->pos - inst->pos;
    }
}

void handle_label(data_t *data)
{
    inst_t *t_inst = data->inst;
    label_t *t_label = NULL;

    while (t_inst) {
        for (int i = 0; i < MAX_ARGS_NUMBER; i++)
            calc_arg_dist(data, t_inst, t_label, i);
        t_inst = t_inst->next;
    }
}
