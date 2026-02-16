/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** load_input.c
*/

#include "my.h"

static void remove_comment(char *line)
{
    if (line[0] == '#' && line[1] == '#')
        return;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != '#')
            continue;
        if (line[i + 1] == '#')
            continue;
        line[i] = '\0';
        return;
    }
}

static void remove_breakline(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == '\n') {
            line[i] = '\0';
            return;
        }
    }
}

static char **fill_buffer(node_t *head, int len_buf)
{
    char **buf = malloc(sizeof(char *) * (len_buf + 1));
    node_t *current = head;
    int index = 0;

    if (!buf)
        return NULL;
    while (current) {
        buf[index] = current->line;
        current = del_node(current);
        index++;
    }
    buf[len_buf] = NULL;
    return buf;
}

char **load_input(void)
{
    char *line = NULL;
    size_t len = 0;
    node_t *head = NULL;
    int len_buf = 0;

    while (getline(&line, &len, stdin) != -1) {
        remove_breakline(line);
        remove_comment(line);
        if (line[0] == '\0')
            continue;
        head = add_node(head, line);
        line = NULL;
        len_buf++;
    }
    free(line);
    return fill_buffer(head, len_buf);
}
