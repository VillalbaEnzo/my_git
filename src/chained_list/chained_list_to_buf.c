/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-minishell2-7 [WSL: Ubuntu-24.04]
** File description:
** chained_list_to_buf.c
*/

#include "my.h"

static int get_len(node_t *head)
{
    int len = 0;
    node_t *temp = head;

    while (temp) {
        len++;
        temp = temp->next;
    }
    return len;
}

char **chained_list_to_buf(node_t *head)
{
    int len = get_len(head);
    node_t *temp = head;
    char **buf = malloc(sizeof(char *) * (len + 1));
    int idx = 0;

    if (!buf)
        return NULL;
    while (temp) {
        buf[idx] = my_strdup(temp->line);
        idx++;
        temp = temp->next;
    }
    buf[idx] = NULL;
    return buf;
}
