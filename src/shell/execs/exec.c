/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** exec
*/
#include "as_tree.h"
#include "mysh.h"
#include "utils.h"
#include "builtin.h"
#include "cmd_array.h"

static void handle_exec_error(char *cmd_save)
{
    mini_printf(2, "%s: %s.", cmd_save, strerror(errno));
    if (errno == ENOEXEC)
        my_putstr(" Binary file not executable.", 2);
    my_putchar('\n', 2);
    free(cmd_save);
}

static int is_builtin(ast_cmd_t *cmd_node, args_t *args, int i)
{
    int temp_ret = -1;

    if (my_strcmp(bt_array[i].builtin_name, cmd_node->arguments[0]) == 0) {
        swap_fd(cmd_node->redirections, cmd_node->redir_count);
        temp_ret = bt_array[i].builtin(args);
        reset_fds(cmd_node->redirections, cmd_node->redir_count);
        return temp_ret;
    }
    return temp_ret;
}

int exec_builtin(ast_cmd_t *cmd_node, char **envp, data_t *data)
{
    args_t args = (args_t){data, envp, cmd_node->arguments};
    int ret_value = -1;

    for (int i = 0; i < NB_BUILTIN; i++) {
        ret_value = is_builtin(cmd_node, &args, i);
        if (ret_value != -1)
            return ret_value;
    }
    return ret_value;
}

int child_code(ast_cmd_t *cmd_node, char **envp)
{
    char *command_saver = my_strdup(CMD);
    int checker = access(CMD, X_OK);

    if (checker == -1 && errno != EISDIR)
        CMD = handle_path(CMD, envp, command_saver);
    if (cmd_node->redirections)
        swap_fd(cmd_node->redirections, cmd_node->redir_count);
    execve(CMD, cmd_node->arguments, envp);
    handle_exec_error(command_saver);
    exit(1);
}

int parent_code(pid_t cpid)
{
    int ret_status = 0;

    if (waitpid(cpid, &ret_status, WUNTRACED) == -1) {
        perror("waitpid");
        return 84;
    }
    return handle_sig(ret_status);
}

int execute_command(ast_cmd_t *cmd_node, char **envp, data_t *data)
{
    pid_t cpid = 0;
    int is_builtin = 0;

    if (cmd_node == NULL || cmd_node->arguments == NULL ||
        cmd_node->arguments[0] == NULL)
        return 0;
    is_builtin = exec_builtin(cmd_node, envp, data);
    if (is_builtin != -1)
        return is_builtin;
    if (glob_args(cmd_node) == 1)
        return 1;
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return 84;
    }
    if (cpid == 0)
        return child_code(cmd_node, envp);
    else
        return parent_code(cpid);
}

int traverse_tree(struct ast_node *root, data_t *data, char **envp)
{
    if (pre_check_tree(root, true, root->type) == false)
        return 1;
    if (root == NULL)
        return 0;
    switch (root->type) {
        case PIPE:
            return exec_pipe(root->pipe_node, data);
        case COMMAND:
            return execute_command(root->cmd_node, envp, data);
        case SEMI_COLON:
            traverse_tree(root->semic_node->left, data, envp);
            return traverse_tree(root->semic_node->right, data, envp);
        case AND:
            return exec_and(root, data, envp);
        case XOR:
            return exec_or(root, data, envp);
        default:
            return 84;
    }
}
