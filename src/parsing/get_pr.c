/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_pr.c
*/

#include "my.h"
#include "struct.h"

static int read_proc_stat(int pid, char *buffer, size_t size)
{
    char path[64];
    FILE *file;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    file = fopen(path, "r");
    if (!file)
        return 0;
    if (!fgets(buffer, size, file)) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

static void parse_priority_nice(const char *buffer, int *priority, int *nice)
{
    sscanf(buffer,
        "%*d %*[^)]%*c %*c "
        "%*d %*d %*d %*d %*d "
        "%*u %*u %*u %*u "
        "%*u %*u %*d %*d "
        "%d %d",
        priority,
        nice);
}

void get_pr_nice(process_t *p)
{
    char buffer[1024];

    if (!p)
        return;
    if (!read_proc_stat(p->pid, buffer, sizeof(buffer)))
        return;
    parse_priority_nice(buffer, &p->priority, &p->nice);
}
