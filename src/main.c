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

    if (argc != 1 || argv[1] != NULL)
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
