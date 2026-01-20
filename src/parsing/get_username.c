/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_username.c
*/

#include "my.h"
#include "struct.h"
#include <pwd.h>
#include <sys/stat.h>

void get_username_from_pid(process_t *process)
{
    char path[256];
    struct stat st;
    struct passwd *pw;

    if (!process)
        return;
    snprintf(path, sizeof(path), "/proc/%d", process->pid);
    if (stat(path, &st) == -1) {
        my_strcpy(process->user, "unknown");
        return;
    }
    process->uid = st.st_uid;
    pw = getpwuid(st.st_uid);
    if (pw != NULL)
        my_strncpy(process->user, pw->pw_name, 31);
    else
        snprintf(process->user, sizeof(process->user), "%d", st.st_uid);
    process->user[31] = '\0';
}
