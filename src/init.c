/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** inits data
*/
#include "mysh.h"
#include "utils.h"

static char *find_in_env(char **envp, int i, char *to_find)
{
    char *ret_term = NULL;

    if (strncmp(envp[i], to_find, my_strlen(to_find)) == 0
        && envp[i][my_strlen(to_find)] == '=') {
        ret_term = malloc(sizeof(char) *
            (my_strlen(envp[i]) - my_strlen(to_find)));
        if (!ret_term)
            return NULL;
        strcpy(ret_term, envp[i] + my_strlen(to_find) + 1);
    }
    return ret_term;
}

static char *get_env_value(char **envp, char *to_find)
{
    char *ret_term = NULL;

    for (int i = 0; envp[i]; i++) {
        ret_term = find_in_env(envp, i, to_find);
        if (ret_term)
            return ret_term;
    }
    return NULL;
}

static local_var_t *init_var(char **envp)
{
    local_var_t *temp = NULL;
    char *cwd = NULL;
    char *term = NULL;
    char *home = NULL;
    char *user = NULL;

    temp = add_local_var(temp, strdup("status"), strdup("0"));
    cwd = getcwd(NULL, 0);
    temp = add_local_var(temp, strdup("cwd"), cwd ? cwd : strdup(""));
    term = get_env_value(envp, "TERM");
    temp = add_local_var(temp, strdup("term"), term ? term : strdup(""));
    home = get_env_value(envp, "HOME");
    temp = add_local_var(temp, strdup("home"), home ? home : strdup(""));
    user = get_env_value(envp, "USER");
    temp = add_local_var(temp, strdup("user"), user ? user : strdup(""));
    return temp;
}

data_t *init_data(char **envp)
{
    data_t *temp = malloc(sizeof(data_t));

    if (!temp)
        return NULL;
    temp->root = NULL;
    temp->tokens = NULL;
    temp->envp = envp;
    temp->local_vars = init_var(envp);
    temp->aliases = NULL;
    return temp;
}
