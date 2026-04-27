/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** str_replace
*/

#include "mysh.h"
#include "utils.h"

int count_occur(char *src, char *var_name, int name_size)
{
    int count = 0;

    for (int i = 0; src[i] != '\0'; i++) {
        if (strstr(&src[i], var_name) == &src[i]) {
            count++;
            i += name_size - 1;
        }
    }
    return count;
}

char *str_replace(char *src, char *var_name, char *value)
{
    int count = count_occur(src, var_name, strlen(var_name));
    int new_size = strlen(src) + (count * (strlen(value) - strlen(var_name)));
    char *new_str = my_calloc((new_size + 1), sizeof(char));
    int src_pos = 0;

    if (!new_str)
        return NULL;
    for (int i = 0; i < new_size && src[src_pos] != '\0'; i++) {
        if ((src + src_pos) == strstr(src, var_name)) {
            strcpy(&new_str[i], value);
            i += strlen(value) - 1;
            src_pos += strlen(var_name);
        } else {
            new_str[i] = src[src_pos];
            src_pos++;
        }
    }
    free(src);
    return new_str;
}
