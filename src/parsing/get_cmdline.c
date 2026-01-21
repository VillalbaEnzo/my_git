/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_cmdline.c
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char *get_basename(char *path)
{
    char *last = strrchr(path, '/');

    if (last)
        return last + 1;
    return path;
}

static int get_exe_path(process_t *p)
{
    char path[64];
    ssize_t n;

    snprintf(path, sizeof(path), "/proc/%d/exe", p->pid);
    n = readlink(path, p->command, sizeof(p->command) - 1);
    if (n < 0)
        return 0;
    p->command[n] = '\0';
    return 1;
}

static int read_comm_file(int pid, char *comm, size_t comm_size)
{
    char path[64];
    FILE *f;

    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    f = fopen(path, "r");
    if (!f)
        return 0;
    if (!fgets(comm, comm_size, f)) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

static void format_comm_name(char *dest, size_t dest_size, const char *comm)
{
    size_t len = strlen(comm);
    char temp[256];

    strncpy(temp, comm, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';
    if (len > 0 && temp[len - 1] == '\n')
        temp[len - 1] = '\0';
    snprintf(dest, dest_size, "[%s]", temp);
}

static void get_comm_name(process_t *p)
{
    char comm[256];

    if (!read_comm_file(p->pid, comm, sizeof(comm))) {
        strcpy(p->command, "?");
        return;
    }
    format_comm_name(p->command, sizeof(p->command), comm);
}

static int read_cmdline_file(int pid, char *buffer,
    size_t bufsize)
{
    char path[64];
    FILE *f;
    size_t n;

    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
    f = fopen(path, "r");
    if (!f)
        return 0;
    n = fread(buffer, 1, bufsize - 1, f);
    fclose(f);
    if (n == 0)
        return 0;
    buffer[n] = '\0';
    return 1;
}

static int set_command_from_cmdline(process_t *p)
{
    char buffer[512];
    char *base;

    if (!read_cmdline_file(p->pid, buffer, sizeof(buffer)))
        return 0;
    base = get_basename(buffer);
    strncpy(p->command, base, sizeof(p->command) - 1);
    p->command[sizeof(p->command) - 1] = '\0';
    return 1;
}

void get_cmdline(process_t *p)
{
    if (!p)
        return;
    if (set_command_from_cmdline(p))
        return;
    if (get_exe_path(p))
        return;
    get_comm_name(p);
}
