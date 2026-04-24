/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** count_args
*/
#include <unistd.h>
#include "mysh.h"
#include "utils.h"

int count_args(char **arg_array, int last_pos)
{
    int count = 0;

    for (; arg_array[last_pos] != NULL && is_operator(arg_array[last_pos])
        != 1 && is_symbol(arg_array[last_pos]) != 1; last_pos++)
        count++;
    return count;
}
