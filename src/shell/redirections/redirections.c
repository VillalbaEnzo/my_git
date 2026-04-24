/*
** EPITECH PROJECT, 2026
** minishell2 [WSL: Ubuntu]
** File description:
** redirections
*/

#include "as_tree.h"
#include "mysh.h"
#include "utils.h"

static void print_invite(void)
{
    if (isatty(STDIN_FILENO))
        mini_printf(1, "? ");
}

static void fill_heredoc(int write_fd, const char *filename)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        print_invite();
        if (getline(&line, &len, stdin) == -1)
            break;
        line[strlen(line) - 1] = '\0';
        if (!my_strcmp(line, filename))
            break;
        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
    }
    free(line);
}

static int open_file(redir_type_t redir_type, const char *filename)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    switch (redir_type) {
        case SIMPLE_R:
            return open(filename, O_WRONLY | O_CREAT, mode);
        case SIMPLE_L:
            return open(filename, O_RDONLY);
        case DOUBLE_R:
            return open(filename, O_WRONLY | O_APPEND | O_CREAT, mode);
        case DOUBLE_L:
        case NOT_R:
            return -1;
    }
}

void redirect_stdout(redir_t *redirection)
{
    int file_fd = open_file(redirection->type, redirection->filename);

    if (file_fd == -1)
        return;
    redirection->save = dup(1);
    if (dup2(file_fd, 1) == -1)
        perror("dup2");
    close(file_fd);
}

static int heredoc_pipe(int fd[2])
{
    if (dup2(fd[0], STDIN_FILENO) == -1) {
        close(fd[0]);
        return -1;
    }
    close(fd[0]);
    return 0;
}

void here_docs(redir_t *redir, const char *filename)
{
    int fd[2];

    if (pipe(fd) == -1)
        return;
    redir->save = dup(STDIN_FILENO);
    fill_heredoc(fd[1], filename);
    close(fd[1]);
    if (heredoc_pipe(fd) == -1)
        return;
}

void redirect_stdin(redir_t *redirection)
{
    int file_fd = open_file(redirection->type, redirection->filename);

    if (file_fd == -1)
        return;
    redirection->save = dup(STDIN_FILENO);
    if (dup2(file_fd, STDIN_FILENO) == -1)
        perror("dup2");
    close(file_fd);
}

void swap_fd(redir_t *redir_array, int redir_count)
{
    for (int i = 0; i < redir_count; i++) {
        switch (redir_array[i].type) {
            case SIMPLE_R:
            case DOUBLE_R:
                redirect_stdout(&redir_array[i]);
                break;
            case SIMPLE_L:
                redirect_stdin(&redir_array[i]);
                break;
            case DOUBLE_L:
                here_docs(&redir_array[i], redir_array[i].filename);
                break;
            case NOT_R:
                return;
        }
    }
}
