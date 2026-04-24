/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** cmd_sub
*/
#include "mysh.h"
#include "utils.h"

static size_t get_cmd_size(char *cmd_pos)
{
    size_t count = 1;

    for (; cmd_pos[count] != '`'; count++);
    return count + 1;
}

static char *find_cmd_group(char *token)
{
    char *cmd_group = NULL;
    char *pos = strchr(token, '`');
    size_t cmd_size = 0;

    if (pos == NULL)
        return NULL;
    cmd_size = get_cmd_size(pos);
    if (cmd_size == 0)
        return "";
    cmd_group = malloc(sizeof(char) * (cmd_size + 1));
    if (!cmd_group)
        return NULL;
    cmd_group = strncpy(cmd_group, pos, cmd_size);
    cmd_group[cmd_size] = '\0';
    return cmd_group;
}

static char *remove_backticks(char *cmd_group)
{
    size_t unticked_size = strlen(cmd_group) - 2;
    char *unticked_cmd = NULL;
    char *temp = cmd_group + 1;

    if (unticked_size == 0)
        return NULL;
    unticked_cmd = malloc(sizeof(char) * (unticked_size + 1));
    if (!unticked_cmd)
        return NULL;
    unticked_cmd = strncpy(unticked_cmd, temp, unticked_size);
    unticked_cmd[unticked_size] = '\0';
    return unticked_cmd;
}

static char **tokenize_cmd(char *cmd_group)
{
    char *cmd_line = remove_backticks(cmd_group);
    char **cmd_tokens = NULL;

    if (cmd_line == NULL)
        return NULL;
    cmd_tokens = str_to_token_array_delim(cmd_line, ' ');
    if (cmd_tokens == NULL)
        return free_return(cmd_line);
    free(cmd_line);
    return cmd_tokens;
}

char *command_sub(char *token, data_t *data)
{
    char *cmd_found = NULL;
    char **cmd_tokens = NULL;
    char *expanded_cmd = NULL;

    while (strchr(token, '`')) {
        cmd_found = find_cmd_group(token);
        if (cmd_found == NULL)
            return NULL;
        cmd_tokens = tokenize_cmd(cmd_found);
        expanded_cmd = expand_cmd(cmd_tokens, data);
        if (expanded_cmd == NULL)
            return free_return(cmd_found);
        token = str_replace(token, cmd_found, expanded_cmd);
        free(expanded_cmd);
        free(cmd_found);
    }
    return token;
}
