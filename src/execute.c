/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** execute.c
*/

#include "../include/my.h"

static bool set_grps(data_t *data)
{
    int nbr_of_grp = 0;
    gid_t *list_gid = NULL;

    while (data->in_group_id[nbr_of_grp])
        nbr_of_grp++;
    list_gid = malloc(sizeof(gid_t) * nbr_of_grp);
    if (list_gid == NULL)
        return false;
    for (int i = 0; i < nbr_of_grp; i++)
        list_gid[i] = (gid_t)atoi(data->in_group_id[i]);
    if (setgroups(nbr_of_grp, list_gid) == -1) {
        return false;
        free(list_gid);
    }
    free(list_gid);
    return true;
}

bool execute(data_t *data)
{
    if (!set_grps(data))
        return false;
    printf("%i\n", data->gid);
    if (setgid(data->gid) == -1)
        return false;
    if (setuid(data->uid) == -1)
        return false;
    if (execvp(data->command[0], data->command) == -1)
        return false;
    return true;
}
