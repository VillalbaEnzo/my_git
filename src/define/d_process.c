/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_process.c
*/

#include "struct.h"
#include "stdlib.h"

process_t *init_process(void)
{
    process_t *proc = malloc(sizeof(process_t));
    int i;
    char *ptr;

    if (proc == NULL)
        return NULL;
    ptr = (char *)proc;
    for (i = 0; i < (int)sizeof(process_t); i++)
        ptr[i] = 0;
    proc->selected = 0;
    return proc;
}
