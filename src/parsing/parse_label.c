/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_label.c
*/

#include "op.h"

static char *get_label(char *line)
{
    int i = 0;
    char *name = NULL;

    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') {
        if (line[i] == LABEL_CHAR)
            break;
        i++;
    }
    if (line[i] != LABEL_CHAR)
        return NULL;
    name = my_calloc(i + 1, sizeof(char));
    if (!name)
        return NULL;
    my_strncpy(name, line, i);
    return name;
}

label_t *parse_label(char *line)
{
    label_t *new_label = NULL;
    char *name = NULL;

    if (!line || line[0] == '\0')
        return NULL;
    name = get_label(line);
    if (!name)
        return NULL;
    new_label = my_calloc(1, sizeof(label_t));
    if (!new_label) {
        free(name);
        return NULL;
    }
    new_label->name = name;
    new_label->pos = 0;
    new_label->next = NULL;
    return new_label;
}
