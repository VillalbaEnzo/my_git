/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** set.c
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static int is_valid_var_name(char *name)
{
    if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' &&
                name[0] <= 'Z'))) {
        mini_printf(2, "set: Variable name must begin with a letter.\n");
        return 0;
    }
    for (int i = 1; name[i] != '\0' && name[i] != '='; i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z') ||
                (name[i] >= 'A' && name[i] <= 'Z') ||
                (name[i] >= '0' && name[i] <= '9') ||
                name[i] == '_')) {
            mini_printf(2, "set: Illegal variable name.\n");
            return 0;
        }
    }
    return 1;
}

static void print_set(args_t *args)
{
    local_var_t *temp = args->data->local_vars;

    while (temp) {
        if (temp->value && my_strlen(temp->value) > 0)
            printf("%s\t%s\n", temp->name, temp->value);
        else printf("%s\n", temp->name);
        temp = temp->next;
    }
}

static int find_equal(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '=')
            return i;
    }
    return -1;
}

static local_var_t *split(char *str, int equal, local_var_t *head)
{
    local_var_t *temp = head;
    char *var = NULL;
    char *value = NULL;

    var = malloc(sizeof(char) * (equal + 1));
    if (!var)
        return head;
    value = malloc(sizeof(char) * (my_strlen(str) - equal));
    if (!value) {
        free(var);
        return head;
    }
    strncpy(var, str, equal);
    var[equal] = '\0';
    strcpy(value, str + equal + 1);
    return add_local_var(temp, var, value);
}

static int set_var(char **args, data_t *data)
{
    int t_size = 0;
    int equal = 0;

    while (args[t_size])
        t_size++;
    if (t_size == 2) {
        equal = find_equal(args[1]);
        if (equal != -1)
            data->local_vars = split(args[1], equal, data->local_vars);
        else data->local_vars = add_local_var(data->local_vars,
            my_strdup(args[1]), my_strdup(""));
    } else if (t_size == 4 && my_strcmp(args[2], "=") == 0)
        data->local_vars = add_local_var(data->local_vars,
            my_strdup(args[1]), my_strdup(args[3]));
    return 0;
}

int set(args_t *args)
{
    if (!args->args[1]) {
        print_set(args);
        return 0;
    }
    if (!is_valid_var_name(args->args[1]))
        return 1;
    set_var(args->args, args->data);
    return 0;
}
