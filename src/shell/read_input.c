/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** read_input
*/
#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static int is_space(char input_char)
{
    return (input_char == ' ');
}

bool is_op_or_sym_c(char c)
{
    char to_comp[2] = {c, '\0'};
    bool answer = false;

    answer = is_operator(to_comp) || is_symbol(to_comp);
    return (answer);
}

bool is_space_needed(char c, char next_c)
{
    if (((!is_space(c) && !is_op_or_sym_c(c)) && is_op_or_sym_c(next_c)) ||
        (is_op_or_sym_c(c) && (!is_space(next_c) && !is_op_or_sym_c(next_c)
                && next_c != '\0')))
        return true;
    return false;
}

static int formatted_size(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (is_space(input[i]) && (is_space(input[i + 1]) || count == 0
                || input[i + 1] == '\0'))
            continue;
        if (is_space_needed(input[i], input[i + 1]))
            count++;
        count++;
    }
    return count;
}

static char *remove_new_line(char *input)
{
    int new_size = my_strlen(input);
    char *new_input = malloc(sizeof(char) * new_size);

    new_input = my_strncpy(new_input, input, new_size - 1);
    new_input[new_size - 1] = '\0';
    free(input);
    return new_input;
}

char *remove_tabs(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\t')
            input[i] = ' ';
    }
    return input;
}

char *format_input(char *input)
{
    char *f_input = NULL;
    int new_size = 0;
    int count = 0;

    input = remove_tabs(input);
    new_size = formatted_size(input);
    f_input = malloc(sizeof(char) * (new_size + 1));
    for (int i = 0; input[i] != '\0'; i++) {
        if (is_space(input[i]) && (is_space(input[i + 1]) || count == 0
                || input[i + 1] == '\0'))
            continue;
        f_input[count] = input[i];
        count++;
        if (is_space_needed(input[i], input[i + 1])) {
            f_input[count] = ' ';
            count++;
        }
    }
    f_input[new_size] = '\0';
    return f_input;
}

char *read_input(data_t *data, int ret_value, int is_term)
{
    char *input = NULL;
    char *formatted_input = NULL;
    size_t trash = 0;

    if (getline(&input, &trash, stdin) == -1) {
        free(input);
        if (is_term == 1)
            mini_printf(1, "\n");
        free_data(data);
        exit(ret_value);
    }
    if (!my_strcmp(input, "\n")) {
        free(input);
        return NULL;
    }
    input = remove_new_line(input);
    formatted_input = format_input(input);
    free(input);
    return formatted_input;
}
