/*
** EPITECH PROJECT, 2026
** minishell2 [WSL: Ubuntu]
** File description:
** pipe
*/
#include "as_tree.h"
#include "mysh.h"
#include "utils.h"

static int count_piped_cmds(ast_pipe_t *fp_node)
{
    int count = 0;

    if (!fp_node)
        return 0;
    count++;
    if (fp_node->writer->type == PIPE)
        count += count_piped_cmds(fp_node->writer->pipe_node);
    else
        count++;
    return count;
}

static ast_cmd_t **get_commands(ast_pipe_t *fp_node, int cmd_count)
{
    ast_cmd_t **cmd_array = my_calloc(cmd_count, sizeof(ast_cmd_t *));
    ast_pipe_t *temp = fp_node;
    int cmd_pos = 0;

    if (cmd_array == NULL)
        return NULL;
    for (; temp->writer->type != COMMAND; temp = temp->writer->pipe_node) {
        cmd_array[cmd_pos] = temp->reader->cmd_node;
        cmd_pos++;
    }
    cmd_array[cmd_pos] = temp->reader->cmd_node;
    cmd_pos++;
    cmd_array[cmd_pos] = temp->writer->cmd_node;
    return cmd_array;
}

static void set_end_pipe(int pipefd[][2], int cmd_count)
{
    for (int i = 0; i < cmd_count - 1; i++) {
        close(pipefd[i][PIPE_WRITE]);
        if (i != 0)
            close(pipefd[i][PIPE_READ]);
    }
    if (dup2(pipefd[0][PIPE_READ], STDIN_FILENO) == -1)
        return;
    close(pipefd[0][PIPE_READ]);
}

static void set_first_pipe(int pipefd[][2], int cmd_count)
{
    for (int i = 0; i < cmd_count - 1; i++) {
        close(pipefd[i][PIPE_READ]);
        if (i != cmd_count - 2)
            close(pipefd[i][PIPE_WRITE]);
    }
    if (dup2(pipefd[cmd_count - 2][PIPE_WRITE], STDOUT_FILENO) == -1)
        return;
    close(pipefd[cmd_count - 2][PIPE_WRITE]);
}

static void set_pipe(int pipefd[][2], int position, int cmd_count)
{
    if (position == 0)
        return set_end_pipe(pipefd, cmd_count);
    if (position == cmd_count - 1)
        return set_first_pipe(pipefd, cmd_count);
    for (int i = 0; i < cmd_count - 1; i++) {
        if (i != position)
            close(pipefd[i][PIPE_READ]);
        if (i != position - 1)
            close(pipefd[i][PIPE_WRITE]);
    }
    if (dup2(pipefd[position - 1][PIPE_WRITE], STDOUT_FILENO) == -1 ||
        dup2(pipefd[position][PIPE_READ], STDIN_FILENO) == -1)
        return;
    close(pipefd[position - 1][PIPE_WRITE]);
    close(pipefd[position][PIPE_READ]);
}

void close_all_pipes(int pipefd[][2], int cmd_count)
{
    for (int i = 0; i < cmd_count - 1; i++) {
        close(pipefd[i][PIPE_READ]);
        close(pipefd[i][PIPE_WRITE]);
    }
}

int exec_piped_child(ast_cmd_t *cmd_node, data_t *data)
{
    int is_builtin = 0;

    if (glob_args(cmd_node) == 1)
        return 1;
    is_builtin = exec_builtin(cmd_node, data->envp, data);
    if (is_builtin != -1)
        exit(is_builtin);
    else
        child_code(cmd_node, data->envp);
    exit(0);
}

int execute_childs(ast_pipe_t *p_node, pid_t all_pids[],
    int pipefd[][2], data_t *data)
{
    int cmd_count = count_piped_cmds(p_node);
    ast_cmd_t **cmd_array = get_commands(p_node, cmd_count);

    if (cmd_array == NULL)
        return 1;
    for (int i = 0; i < cmd_count; i++) {
        all_pids[i] = fork();
        if (all_pids[i] == 0) {
            set_pipe(pipefd, i, cmd_count);
            exec_piped_child(cmd_array[i], data);
        }
    }
    free(cmd_array);
    return 0;
}

int exec_pipe(ast_pipe_t *p_node, data_t *data)
{
    int cmd_count = count_piped_cmds(p_node);
    int pipefd[cmd_count - 1][2];
    pid_t all_pids[cmd_count];
    int ret_status[cmd_count];

    for (int i = 0; i < cmd_count - 1; i++) {
        if (pipe(pipefd[i]) == -1)
            return 1;
    }
    execute_childs(p_node, all_pids, pipefd, data);
    close_all_pipes(pipefd, cmd_count);
    for (int i = 0; i < cmd_count; i++)
        waitpid(all_pids[i], &ret_status[i], WUNTRACED);
    for (int i = 0; i < cmd_count; i++) {
        if (ret_status[i] != 0)
            return handle_sig(ret_status[i]);
    }
    return 0;
}
