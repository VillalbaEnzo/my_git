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

static void prog_loop(char **envp, data_t *data, int *ret)
{
    char *input = NULL;
    local_var_t *temp = NULL;
    int is_term = isatty(STDIN_FILENO);

    while (1) {
        data = init_data(envp, temp);
        if (is_term)
            display_prompt();
        input = read_input(data, *ret, is_term);
        data->tokens = tokenizer(input);
        data->root = build_tree(data->tokens);
        *ret = traverse_tree(data->root, data, envp);
        temp = data->local_vars;
        free_data(data);
    }
}

static int init_script_execution(char **argv, data_t *data)
{
    char buffer[32];
    int fd = open(argv[1], O_RDONLY);;

    if (fd == -1) {
        mini_printf(2, "%s: %s.\n", argv[1], strerror(errno));
        return 0;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    data->local_vars = add_local_var(data->local_vars, strdup("0"),
        strdup(argv[1]));
    for (int i = 2; argv[i]; i++) {
        snprintf(buffer, sizeof(buffer), "%d", i - 1);
        data->local_vars = add_local_var(data->local_vars, strdup(buffer),
            strdup(argv[i]));
    }
    return 1;
}

int main(int argc, char **argv, char **envp)
{
    data_t *data = init_data(envp, NULL);
    int ret = 0;

    if (!data)
        return 84;
    if (argc >= 2 && !init_script_execution(argv, data))
        return 84;
    prog_loop(envp, data, &ret);
    return ret;
}
