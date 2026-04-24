/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** exp_cmd
*/

#include "mysh.h"
#include "utils.h"

static void sub_child_exec(struct ast_node *sub_root, int pipe_fd[2],
    data_t *data)
{
    int ret = 0;

    if (dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO) == -1)
        return;
    close(pipe_fd[PIPE_READ]);
    close(pipe_fd[PIPE_WRITE]);
    ret = traverse_tree(sub_root, data, data->envp);
    free_from_root(sub_root);
    free_data(data);
    exit(ret);
}

static char *remove_newlines(char *raw_c_output)
{
    char *clean_input = NULL;
    size_t clean_size = strlen(raw_c_output);
    int clean_input_pos = 0;

    if (clean_size == 0)
        return raw_c_output;
    clean_input = malloc(sizeof(char) * (clean_size + 1));
    clean_input[0] = '\0';
    for (int i = 0; raw_c_output[i] != '\0'; i++) {
        if (raw_c_output[i] != '\n' && raw_c_output[i + 1] != '\0')
            clean_input[clean_input_pos] = raw_c_output[i];
        else
            clean_input[clean_input_pos] = ' ';
        clean_input_pos++;
    }
    clean_input[clean_size] = '\0';
    free(raw_c_output);
    return clean_input;
}

static char *get_sub_input(FILE *c_output)
{
    char *input = NULL;
    size_t thrash = 0;

    input = malloc(sizeof(char));
    input[0] = '\0';
    if (fgetc(c_output) == EOF)
        return input;
    getdelim(&input, &thrash, EOF, c_output);
    return remove_newlines(input);
}

static char *sub_parent(struct ast_node *sub_root, int pipe_fd[2], int cpid)
{
    FILE *child_output = NULL;
    char *cmd_input = NULL;

    free_from_root(sub_root);
    close(pipe_fd[PIPE_WRITE]);
    child_output = fdopen(pipe_fd[PIPE_READ], "r");
    waitpid(cpid, NULL, WUNTRACED);
    cmd_input = get_sub_input(child_output);
    fclose(child_output);
    return cmd_input;
}

static char *execute_sub_tree(struct ast_node *sub_root, data_t *data)
{
    int pipe_fd[2];
    int cpid = 0;

    if (pipe(pipe_fd) == -1)
        return NULL;
    cpid = fork();
    if (cpid == -1)
        return NULL;
    if (cpid == 0)
        sub_child_exec(sub_root, pipe_fd, data);
    else
        return sub_parent(sub_root, pipe_fd, cpid);
    return NULL;
}

char *expand_cmd(char **cmd_tokens, data_t *data)
{
    struct ast_node *sub_root = build_tree(cmd_tokens);
    char *expand_cmd = NULL;

    expand_cmd = execute_sub_tree(sub_root, data);
    return expand_cmd;
}
