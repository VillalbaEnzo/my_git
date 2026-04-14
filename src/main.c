/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** main file
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"
#include "as_tree.h"

int main(int argc, char **argv, char **envp)
{
    data_t *data = NULL;
    int is_term = isatty(STDIN_FILENO);
    int ret = 0;
    char *input = NULL;
    int fd;

    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            mini_printf(2, "%s: %s.\n", argv[1], strerror(errno));
            return 84;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else if (argc != 1 || argv[1])
        return 84;
    while (1) {
        data = init_data(envp);
        if (is_term)
            display_prompt();
        input = read_input(data, ret, is_term);
        data->tokens = tokenizer(input);
        data->root = build_tree(data->tokens);
        ret = traverse_tree(data->root, data, envp);
        free_data(data);
    }
    return ret;
}
