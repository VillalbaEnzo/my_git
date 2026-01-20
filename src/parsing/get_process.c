/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_process.c
*/

#include "dirent.h"
#include "my.h"
#include "struct.h"

static void get_a_pid(inf_t *i, DIR *dir, struct dirent *entry)
{
    char *endptr;
    long pid;

    if (!i || !dir)
        return;
    entry = readdir(dir);
    while (entry != NULL) {
        pid = strtol(entry->d_name, &endptr, 10);
        if (*endptr != '\0') {
            entry = readdir(dir);
            continue;
        }
        if (i->process_count >= i->process_capacity)
            return;
        i->processes[i->process_count].pid = (pid_t)pid;
        i->process_count++;
        entry = readdir(dir);
    }
}

void get_user(top_t *t)
{
    DIR *dir = opendir("/proc");
    struct dirent *entry = NULL;

    if (!dir)
        return;
    t->inf->process_count = 0;
    get_a_pid(t->inf, dir, entry);
    get_a_user(t->inf, NULL, NULL);
    closedir(dir);
}
