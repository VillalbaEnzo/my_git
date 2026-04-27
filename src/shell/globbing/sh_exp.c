/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** word_exp
*/

#include "mysh.h"
#include "arg_exp.h"
#include "utils.h"

static bool is_valid_var(char *token)
{
    char *doll_pos = strchr(token, '$');
    int i = 1;

    for (; c_is_alphanum(doll_pos[i]); i++);
    if (i == 1)
        return false;
    return true;
}

static bool is_cmd_sub(char *token)
{
    int backtick_count = 0;

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '`')
            backtick_count++;
    }
    if (backtick_count % 2 == 0 && backtick_count != 0)
        return true;
    else
        return false;
}

char *exp_arg(char *token, token_type_t type, perm_t permissions, data_t *data)
{
    if ((type & permissions) == 0 && permissions != 0)
        return token;
    switch (type) {
        case VAR_SUB:
            return var_substitution(token, data);
        case CMD_SUB:
            return command_sub(token, data);
    }
    return token;
}

token_type_t set_type(char *token, perm_t *permissions)
{
    token_type_t type = 0;

    if (fnmatch("'*'", token, 0) == 0 && *permissions == 0)
        *permissions = (unsigned char)~(CMD_SUB | VAR_SUB);
    if (is_cmd_sub(token))
        type = CMD_SUB;
    if (strchr(token, '$') != NULL && type != CMD_SUB) {
        if (is_valid_var(token))
            type = VAR_SUB;
    }
    return type;
}

int args_exp(ast_cmd_t *cmd_node, data_t *data)
{
    perm_t permissions = 0;
    token_type_t type = 0;

    if (cmd_node->arguments[0] == NULL)
        return 1;
    for (int i = 0; cmd_node->arguments[i] != NULL; i++) {
        type = set_type(cmd_node->arguments[i], &permissions);
        if (type != 0)
            cmd_node->arguments[i] = exp_arg(cmd_node->arguments[i], type,
                permissions, data);
        if (!cmd_node->arguments[i])
            return 1;
    }
    cmd_node->arguments = glob_arg(cmd_node->arguments);
    cmd_node->arguments = quote_removal(cmd_node->arguments);
    if (cmd_node->arguments == NULL)
        return 1;
    return 0;
}
