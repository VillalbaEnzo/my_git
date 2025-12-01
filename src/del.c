/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** del.c
*/

#include "./include/my.h"

static int check_head(context_t *ctx, node_t *current, int id_ref)
{
    if (current->id == id_ref) {
        ctx->head = current->next;
        mini_printf("%s n°%d - \"%s\" deleted.\n",
            enum_type_to_name(current->type), current->id, current->name);
        free(current->name);
        free(current);
        return 1;
    }
    return 0;
}

static int del_one(context_t *ctx, int id_ref)
{
    node_t *current = ctx->head;
    node_t *prev = NULL;

    if (current == NULL)
        return 84;
    if (check_head(ctx, current, id_ref))
        return 0;
    while (current != NULL && current->id != id_ref) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return 84;
    prev->next = current->next;
    mini_printf("%s n°%d - \"%s\" deleted.\n",
        enum_type_to_name(current->type), current->id, current->name);
    free(current->name);
    free(current);
    return 0;
}

int del(void *data, char **args)
{
    context_t *ctx = data;

    if (args[0] == NULL)
        return 0;
    del_one(ctx, my_getnbr(args[0]));
    return del(data, args + 1);
}
