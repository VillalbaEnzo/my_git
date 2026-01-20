/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mytop-5
** File description:
** get_memory.c
*/

#include "my.h"
#include "struct.h"
#include "dirent.h"

static void read_statm_file(process_t *proc)
{
    char path[256];
    char buf[256];
    char **buf_a = NULL;
    FILE *fp = NULL;

    snprintf(path, sizeof(path), "/proc/%d/statm", proc->pid);
    fp = fopen(path, "r");
    if (!fp)
        return;
    if (fgets(buf, sizeof(buf), fp) != NULL) {
        buf_a = my_str_to_word_array(buf);
        if (buf_a && buf_a[0] && buf_a[1] && buf_a[2]) {
            proc->virt_memory = atoi(buf_a[0]);
            proc->res_memory = atoi(buf_a[1]);
            proc->shared_memory = atoi(buf_a[2]);
        }
        free(buf_a);
    }
    fclose(fp);
}

static void get_mem_infos(top_t *t, DIR *dir, struct dirent *entry)
{
    if (!t || !t->inf)
        return;
    for (int j = 0; j < t->inf->process_count; j++) {
        read_statm_file(&t->inf->processes[j]);
    }
}

void get_memory(top_t *t)
{
    DIR *dir = opendir("/proc");
    struct dirent *entry = NULL;

    if (!dir)
        return;
    printf("bef get_mem");
    get_mem_infos(t, dir, entry);
    printf("af get_mem");
    closedir(dir);
}
