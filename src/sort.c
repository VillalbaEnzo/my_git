/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** sort.c
*/

#include "./include/my.h"

static int get_cmp_result(node_t *node_a, node_t *node_b, char *arg)
{
    if (my_strcmp(arg, "TYPE") == 0)
        return (int)node_a->type - (int)node_b->type;
    if (my_strcmp(arg, "ID") == 0)
        return node_a->id - node_b->id;
    if (my_strcmp(arg, "NAME") == 0)
        return my_strcmp(node_a->name, node_b->name);
    return 0;
}

static int nodes_compare(node_t *node_a, node_t *node_b, char **args)
{
    int i = 0;
    int invers = 1;
    int result = 0;

    while (args[i]) {
        if (my_strcmp(args[i], "-r") == 0)
            i++;
        invers = 1;
        if (args[i + 1] && my_strcmp(args[i + 1], "-r") == 0)
            invers = -1;
        result = get_cmp_result(node_a, node_b, args[i]);
        if (result != 0)
            return result * invers;
        i++;
        if (invers == -1)
            i++;
    }
    return 0;
}

static void split_list(node_t *source, node_t **first_ref, node_t **seconde_ref)
{
    node_t *fast;
    node_t *slow;

    if (source == NULL || source->next == NULL) {
        *first_ref = source;
        *seconde_ref = NULL;
        return;
    }
    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *first_ref = source;
    *seconde_ref = slow->next;
    slow->next = NULL;
}

node_t *merge(node_t *a, node_t *b, char **args)
{
    node_t *result = NULL;

    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (nodes_compare(a, b, args) <= 0) {
        result = a;
        result->next = merge(a->next, b, args);
    } else {
        result = b;
        result->next = merge(a, b->next, args);
    }
    return result;
}

void merge_sort(node_t **head_ref, char **args)
{
    node_t *head = *head_ref;
    node_t *a = NULL;
    node_t *b = NULL;

    if (head == NULL || head->next == NULL)
        return;
    split_list(head, &a, &b);
    merge_sort(&a, args);
    merge_sort(&b, args);
    *head_ref = merge(a, b, args);
}

int sort(void *data, char **args)
{
    context_t *ctx = data;

    if (args == NULL || args[0] == NULL)
        return 84;
    merge_sort(&ctx->head, args);
    return 0;
}
