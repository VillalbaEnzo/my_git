/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** add.c
*/

#include "./include/my.h"

static int check_active_type(char *arg, node_t *node)
{
    if (my_strcmp(arg, "ACTUATOR") == 0) {
        node->type = ACTUATOR;
        return 1;
    }
    if (my_strcmp(arg, "PROCESSOR") == 0) {
        node->type = PROCESSOR;
        return 1;
    }
    return 0;
}

static int check_passive_type(char *arg, node_t *node)
{
    if (my_strcmp(arg, "DEVICE") == 0) {
        node->type = DEVICE;
        return 1;
    }
    if (my_strcmp(arg, "SENSOR") == 0) {
        node->type = SENSOR;
        return 1;
    }
    if (my_strcmp(arg, "WIRE") == 0) {
        node->type = WIRE;
        return 1;
    }
    return 0;
}

static int chek_type(char *arg, node_t *node)
{
    if (check_active_type(arg, node) == 0 && check_passive_type(arg, node) == 0)
        return 0;
    return 1;
}

static int file_list(void *data, char **args)
{
    context_t *ctx = data;
    node_t *new_node;

    if (args[0] == NULL)
        return 0;
    new_node = malloc(sizeof(node_t));
    if (!new_node)
        return 84;
    if (!chek_type(args[0], new_node)) {
        free(new_node);
        return 84;
    }
    new_node->name = my_strdup(args[1]);
    new_node->id = ctx->next_id;
    ctx->next_id += 1;
    new_node->next = ctx->head;
    ctx->head = new_node;
    mini_printf("%s n°%d - \"%s\" added.\n", args[0], new_node->id,
        new_node->name);
    return add(data, args + 2);
}

int add(void *data, char **args)
{
    int nbr_args = 0;

    while (args[nbr_args])
        nbr_args++;
    if (nbr_args % 2 != 0)
        return 84;
    return file_list(data, args);
}
