/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-settingup-45
** File description:
** open_read.c
*/

#include "my.h"

char **open_read(void)
{
    char **buf;
    char *line = NULL;
    size_t len = 0;
    node_t *head = NULL;
    node_t *current;
    int len_buf = 0;
    int index = 0;

    while (getline(&line, &len, stdin) != -1) {
        head = add_node(head, line);
        len_buf++;
    }
    buf = malloc(sizeof(char *) * (len_buf + 1));
    free(line);
    current = head;
    while (current) {
        buf[index] = my_strdup(current->line);
        current = del_node(current);
        index++;
    }
    buf[len_buf] = NULL;
    return buf;
}
