/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** disp.c
*/

#include "./include/my.h"

int disp(void *data, char **args)
{
    context_t *ctx = data;
    node_t *current = ctx->head;

    while (current != NULL) {
        mini_printf("%s n°%d - \"%s\"\n",
            enum_type_to_name(current->type), current->id, current->name);
        current = current->next;
    }
    return 0;
}
