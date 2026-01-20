/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_sys.c
*/

#include "my.h"
#include "stdlib.h"

system_t *init_system(void)
{
    system_t *sys = malloc(sizeof(system_t));
    int i;
    char *ptr;

    if (sys == NULL)
        return NULL;
    ptr = (char *)sys;
    for (i = 0; i < (int)sizeof(system_t); i++)
        ptr[i] = 0;
    sys->mem_unit_process = 1;
    sys->mem_unit_system = 1;
    return sys;
}
