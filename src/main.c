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
    int is_term = isatty(STDIN_FILENO);

    while (1) {
        data = init_data(envp);
        if (is_term)
            display_prompt();
        input = read_input(data, *ret, is_term);
        data->tokens = tokenizer(input);
        data->root = build_tree(data->tokens);
        *ret = traverse_tree(data->root, data, envp);
        free_data(data);
    }
}

static local_var_t *add_local_var(local_var_t *head, char *name, char *value)
{
    local_var_t *new_node = malloc(sizeof(local_var_t));
    local_var_t *temp = NULL;

    if (!new_node)
        return head;
    new_node->name = name;
    new_node->value = value;
    new_node->next = NULL;
    if (head == NULL)
        return new_node;
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return head;
}

static int open_file_script(char **argv, data_t *data)
{
    char buffer[32];
    int fd = open(argv[1], O_RDONLY);;

    if (fd == -1) {
        mini_printf(2, "%s: %s.\n", argv[1], strerror(errno));
        return 0;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    for (int i = 2; argv[i]; i++) {
        snprintf(buffer, sizeof(buffer), "%d", i);
        data->local_vars = add_local_var(data->local_vars, strdup(buffer), argv[i]);
    }
    return 1;
}

int main(int argc, char **argv, char **envp)
{
    data_t *data = init_data(envp);
    int ret = 0;

    if (argc >= 2 && !open_file_script(argv, data))
        return 84;
    while (data->local_vars) {
        printf("nom = %s, valeur = %s\n", data->local_vars->name,
            data->local_vars->value);
        data->local_vars = data->local_vars->next;
    }
    if (argc != 1 && argc != 2)
        return 84;
    prog_loop(envp, data, &ret);
    return ret;
}
