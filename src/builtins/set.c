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

static bool has_equal(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '=')
            return true;
    }
    return false;
}

static int set_var(args_t *args)
{
    printf("test\n");
    // int i = 1;

    // while (args->args[i]) {
    //     if (has_equal(args->args[i])) {

    //     } else if (strcmp(args->args[i + 1], "=") == 0) {

    //     } else {

    //     }
    // }
}

// int handle_set(args_t *args)

int set(args_t *args)
{
    int len = 0;

    if (!args->args[1]) {
        print_set(args);
        return 0;
    }
    if (!is_valid_var_name(args->args[1]))
        return 1;
    set_var(args);
    return 0;
}
