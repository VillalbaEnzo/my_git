/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** read_input
*/
#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static void check_flow_diff(char *token, char *last_token, int *diff,
    bool *is_elif)
{
    if (my_strcmp(token, "foreach") == 0 || my_strcmp(token, "while") == 0)
        (*diff)++;
    if (my_strcmp(token, "endif") == 0 || my_strcmp(token, "end") == 0)
        (*diff)--;
    if (my_strcmp(token, "if") == 0 && last_token && !my_strcmp(last_token,
            "else"))
        *is_elif = true;
}

static int count_line_blocks(char *input)
{
    int diff = 0;
    char *temp = my_strdup(input);
    char *token = strtok(temp, " \t\n");
    char *last_token = NULL;
    bool is_elif = false;

    while (token) {
        check_flow_diff(token, last_token, &diff, &is_elif);
        last_token = token;
        token = strtok(NULL, " \t\n");
    }
    if (last_token && my_strcmp(last_token, "then") == 0 && !is_elif)
        diff++;
    free(temp);
    return diff;
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
    int open_blocks = 0;

    while (1) {
        input = read_line(data, ret_value, is_term);
        input = remove_new_line(input);
        open_blocks += count_line_blocks(input);
        full_input = add_input(full_input, input);
        free(input);
        if (open_blocks <= 0)
            break;
        if (is_term)
            mini_printf(1, "? ");
    }
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
