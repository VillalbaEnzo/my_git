/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** read_input
*/
#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static int get_open_blocks(char *input)
{
    int open_blocks = 0;
    char *temp = my_strdup(input);
    char *token = strtok(temp, " \t\n");

    while (token != NULL) {
        if (my_strcmp(token, "if") == 0 || my_strcmp(token, "foreach") == 0)
            open_blocks++;
        if (my_strcmp(token, "endif") == 0 || my_strcmp(token, "end") == 0)
            open_blocks--;
        token = strtok(NULL, " \t\n");
    }
    free(temp);
    return open_blocks;
}

static char *add_input(char *full_input, char *new_input)
{
    char *temp = NULL;
    int len = 0;

    if (!full_input)
        return my_strdup(new_input);
    len = my_strlen(full_input) + my_strlen(new_input) + 2;
    temp = malloc(sizeof(char) * len);
    if (!temp)
        return NULL;
    strcpy(temp, full_input);
    strcat(temp, " ");
    strcat(temp, new_input);
    free(full_input);
    return temp;
}

static char *read_line(data_t *data, int ret_value, int is_term)
{
    char *input = NULL;
    size_t trash = 0;

    if (getline(&input, &trash, stdin) == -1) {
        free(input);
        if (is_term)
            mini_printf(1, "\n");
        free_data(data);
        exit(ret_value);
    }
    return input;
}

static char *get_full_input(data_t *data, int ret_value, int is_term)
{
    char *full_input = my_strdup("");
    char *input = NULL;

    while (1) {
        input = read_line(data, ret_value, is_term);
        input = remove_new_line(input);
        full_input = add_input(full_input, input);
        if (get_open_blocks(full_input) <= 0)
            break;
        if (is_term)
            mini_printf(1, "? ");
        free(input);
    }
    free(input);
    return full_input;
}

char *read_input(data_t *data, int ret_value, int is_term)
{
    char *full_input = get_full_input(data, ret_value, is_term);
    char *formatted_input = NULL;

    full_input = change_all_vars(full_input, data->local_vars);
    formatted_input = format_input(full_input);
    free(full_input);
    if (formatted_input && formatted_input[0] == '\0') {
        free(formatted_input);
        return NULL;
    }
    return formatted_input;
}
