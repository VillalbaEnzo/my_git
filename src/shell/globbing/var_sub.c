/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** var_sub
*/

#include "mysh.h"
#include "utils.h"

static size_t get_var_size(char *var_given)
{
    size_t count = 0;

    for (; c_is_alphanum(var_given[count + 1]); count++);
    return count;
}

static char *env_lk(char *var_name, char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], (var_name + 1), strlen(var_name) - 1) == 0)
            return (strchr(envp[i], '=') + 1);
    }
    return NULL;
}

static char *undef_err(char *var_name)
{
    mini_printf(1, "%s: Undefined variable.\n", (var_name + 1));
    return NULL;
}

static char *loc_var_lk(char *var_name, local_var_t *loc_vars)
{
    local_var_t *temp = loc_vars;

    for (; temp != NULL; temp = temp->next) {
        if (strcmp(var_name + 1, temp->name) == 0)
            return temp->value;
    }
    return undef_err(var_name);
}

static char *get_var_val(char *var_name, data_t *data)
{
    char *var_val = env_lk(var_name, data->envp);

    if (var_val == NULL)
        var_val = loc_var_lk(var_name, data->local_vars);
    return var_val;
}

static char *find_var_name(char *token)
{
    char *var_pos = strchr(token, '$');
    size_t var_size = get_var_size(var_pos) + 1;
    char *var_name = malloc(sizeof(char) * (var_size + 1));

    if (!var_name)
        return NULL;
    var_name = strncpy(var_name, var_pos, var_size);
    var_name[var_size] = '\0';
    return var_name;
}

char *var_substitution(char *to_sub, data_t *data)
{
    char *var_found = NULL;
    char *var_value = NULL;

    while (strchr(to_sub, '$')) {
        var_found = find_var_name(to_sub);
        if (var_found == NULL)
            return NULL;
        var_value = get_var_val(var_found, data);
        if (var_value == NULL)
            return NULL;
        to_sub = str_replace(to_sub, var_found, var_value);
        free(var_found);
    }
    return to_sub;
}
