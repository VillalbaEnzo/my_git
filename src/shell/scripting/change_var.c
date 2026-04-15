/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** change_var.c
*/

#include "mysh.h"

static int is_var_char(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_')
        return 1;
    return 0;
}

char *get_var_value(local_var_t *local_vars, char *var_name)
{
    local_var_t *temp = local_vars;

    while (temp) {
        if (strcmp(temp->name, var_name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return "";
}

char *extract_var_name(char *ptr, int *len)
{
    int i = 1;
    char *var_name = NULL;

    while (ptr[i] != '\0' && is_var_char(ptr[i]))
        i++;
    *len = i - 1;
    if (*len == 0)
        return NULL;
    var_name = malloc(sizeof(char) * (*len + 1));
    if (!var_name)
        return NULL;
    strncpy(var_name, ptr + 1, *len);
    var_name[*len] = '\0';
    return var_name;
}

char *create_ret_str(char *line, char *ptr, char *val, int var_len)
{
    int prefix_len = 0;
    int value_len = 0;
    int suffix_len = 0;
    char *ret = NULL;

    prefix_len = ptr - line;
    value_len = strlen(val);
    suffix_len = strlen(ptr + var_len + 1);
    ret = malloc(sizeof(char) * (prefix_len + value_len + suffix_len + 1));
    if (!ret)
        return NULL;
    strncpy(ret, line, prefix_len);
    ret[prefix_len] = '\0';
    strcat(ret, val);
    strcat(ret, ptr + var_len + 1);
    return (ret);
}

char *replace_var(char *line, local_var_t *local_vars)
{
    char *ptr = NULL;
    char *var_name = NULL;
    char *var_value = NULL;
    char *new_str = NULL;
    int var_name_len = 0;

    ptr = strchr(line, '$');
    if (!ptr)
        return (strdup(line));
    var_name = extract_var_name(ptr, &var_name_len);
    if (!var_name)
        return (strdup(line));
    var_value = get_var_value(local_vars, var_name);
    new_str = create_ret_str(line, ptr, var_value, var_name_len);
    free(var_name);
    return (new_str);
}
