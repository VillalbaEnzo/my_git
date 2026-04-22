/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** exit shell
*/
#include "mysh.h"
#include "as_tree.h"
#include "builtin.h"
#include "utils.h"

int exitsh(args_t *args)
{
    free_data(args->data);
    exit(0);
}
