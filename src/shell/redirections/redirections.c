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
    mini_printf(1, "? ");
}

static void read_line(char **input)
{
    size_t thrash = 0;

    getline(input, &thrash, stdin);
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

void here_docs(redir_t *redir, const char *filename)
{
    char *input = NULL;
    int to_write_fd = 0;

    redir->save = dup(STDIN_FILENO);
    if (dup2(to_write_fd, STDIN_FILENO) == -1)
        return;
    while (my_strncmp(input, filename, my_strlen(filename)) != 0) {
        mini_printf(to_write_fd, input);
        print_invite();
        read_line(&input);
    }
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
