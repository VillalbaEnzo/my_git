/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_user.c
*/

#include "dirent.h"
#include "my.h"
#include "struct.h"

void get_a_user(inf_t *i, DIR *dir, struct dirent *entry)
{
    if (!i)
        return;
    for (int j = 0; j < i->process_count; j++) {
        get_username_from_pid(&i->processes[j]);
    }
}
