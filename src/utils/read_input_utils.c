/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** read_line_utils.c
*/

#include "mysh.h"
#include "builtin.h"
#include "utils.h"

static int is_space(char input_char)
{
    return (input_char == ' ');
}

static bool is_op_or_sym_c(char c)
{
    char to_comp[2] = {c, '\0'};
    bool answer = false;

    answer = is_operator(to_comp) || is_symbol(to_comp);
    return (answer);
}

static bool is_space_needed(char c, char next_c)
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

static char *remove_tabs_and_comment(char *input)
{
    int is_string = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"')
            is_string += 1;
        if (input[i] == '\t')
            input[i] = ' ';
        if (input[i] == '#' && (is_string % 2 == 0)) {
            input[i] = '\0';
            break;
        }
    }
    return input;
}

char *remove_new_line(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n' || input[i] == '\r') {
            input[i] = '\0';
            break;
        }
    }
    return input;
}

char *format_input(char *input)
{
    char *f_input = NULL;
    int new_size = 0;
    int count = 0;

    input = remove_tabs_and_comment(input);
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
