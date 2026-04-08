/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** free_data
*/

#include "op.h"

void free_labels(label_t *label)
{
    label_t *save = NULL;

    while (label) {
        save = label;
        free(label->name);
        label = label->next;
        free(save);
    }
}

void free_args(inst_t *inst)
{
    for (int i = 0; inst->args[i].type != 0; i++) {
        if (inst->args[i].label)
            free(inst->args[i].label);
    }
}

void free_inst(inst_t *inst)
{
    inst_t *save = NULL;

    while (inst) {
        save = inst;
        free_args(inst);
        inst = inst->next;
        free(save);
    }
}

/**
 * Frees every allocated data
 * @param data data to free
*/
void free_data(data_t *data)
{
    free(data->filename);
    if (data->labels)
        free_labels(data->labels);
    free(data->header);
    free_inst(data->inst);
    free(data);
}
