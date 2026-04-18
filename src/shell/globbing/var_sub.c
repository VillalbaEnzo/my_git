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

    for (; var_given[count + 1] != '\0' && var_given[count + 1] != ' '
        && var_given[count + 1] != '"'; count++);
    return count;
}

static char *replace_token(char *var_value, char *token)
{
    char *cut_pos = strchr(token, '$');
    char *new_val = NULL;

    if (var_value == NULL)
        return NULL;
    if (cut_pos == token)
        return strdup(var_value);
    else {
        *cut_pos = '\0';
        if (asprintf(&new_val, "%s%s", token, var_value) == -1)
            return NULL;
        return new_val;
    }
}

static char *sub_env_var(char *var, char *to_sub)
{
    char *var_save = var;
    char *new_val = NULL;

    while (*var != '=')
        var++;
    var++;
    new_val = replace_token(var, to_sub);
    free(to_sub);
    var = var_save;
    return new_val;
}

static char *undef_err(char *var_given)
{
    size_t err_var_size = get_var_size(var_given);
    char *err_var = malloc(sizeof(char) * (err_var_size + 1));

    if (!err_var)
        return NULL;
    err_var[err_var_size] = '\0';
    err_var = strncpy(err_var, (var_given + 1), err_var_size);
    mini_printf(1, "%s: Undefined variable.\n", err_var);
    free(err_var);
    return NULL;
}

static char *sub_loc_var(local_var_t *loc_vars, char *to_sub)
{
    local_var_t *temp = loc_vars;
    char *var_given = strchr(to_sub, '$');
    char *new_val = NULL;

    for (; temp != NULL; temp = temp->next) {
        if (strncmp((var_given + 1), temp->name, strlen(temp->name)) == 0) {
            new_val = replace_token(temp->value, to_sub);
            free(to_sub);
            return new_val;
        }
    }
    return undef_err(var_given);
}

char *var_substitution(char *to_sub, data_t *data)
{
    int pos = 0;
    char *var_given = strchr(to_sub, '$');
    size_t var_len = get_var_size(var_given);

    for (; data->envp[pos] != NULL; pos++) {
        if (strncmp((var_given + 1), data->envp[pos], var_len) == 0)
            return sub_env_var(data->envp[pos], to_sub);
    }
    return sub_loc_var(data->local_vars, to_sub);
}
