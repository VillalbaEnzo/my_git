/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** d_inf.c
*/

#include "struct.h"
#include "stdlib.h"

static void zero_memory(void *ptr, int size)
{
    char *byte_ptr = (char *)ptr;
    int i;

    for (i = 0; i < size; i++)
        byte_ptr[i] = 0;
}

static void init_inf_defaults(inf_t *inf)
{
    inf->refresh_delay = 3.0;
    inf->max_frames = -1;
    inf->sort_column = 0;
    inf->running = 1;
    inf->need_refresh = 1;
    inf->process_capacity = 100;
    inf->mem_unit_process = 1;
}

static process_t *allocate_processes(int capacity)
{
    process_t *processes = malloc(sizeof(process_t) * capacity);

    if (processes == NULL)
        return NULL;
    zero_memory(processes, sizeof(process_t) * capacity);
    return processes;
}

inf_t *init_inf(void)
{
    inf_t *inf = malloc(sizeof(inf_t));

    if (inf == NULL)
        return NULL;
    zero_memory(inf, sizeof(inf_t));
    init_inf_defaults(inf);
    inf->processes = allocate_processes(inf->process_capacity);
    if (inf->processes == NULL) {
        free(inf);
        return NULL;
    }
    return inf;
}
