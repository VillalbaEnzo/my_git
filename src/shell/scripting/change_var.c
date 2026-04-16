/*
** EPITECH PROJECT, 2025
** G-PSU-200-LYN-2-1-42sh-2 [WSL: Ubuntu-24.04]
** File description:
** change_var.c
*/

#include "mysh.h"
#include "utils.h"

struct idx_s {
    int start;
    int end;
    int size;
};

static char *get_var_value(local_var_t *local_vars, char *var_name)
{
    local_var_t *temp = local_vars;

    while (temp) {
        if (strcmp(temp->name, var_name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return "";
}

static int is_end(char c)
{
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9')
        && (c != '_'))
        return 1;
    return 0;
}

static int var_counter(char *line)
{
    int var_counter = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '$' && !is_end(line[i + 1]))
            var_counter++;
    }
    return var_counter;
}

static struct idx_s get_idx(char *line)
{
    int start = 0;
    int end = 0;
    struct idx_s idx = {-1, -1, -1};

    while (line[start] && line[start] != '$')
        start++;
    if (line[start] == '$')
        idx.start = start;
    if (idx.start == -1)
        return idx;
    end = idx.start + 1;
    while (line[end] && !is_end(line[end]))
        end++;
    idx.end = end;
    if (idx.end == -1)
        return idx;
    idx.size = idx.end - idx.start;
    return idx;
}

static char *strntncpy(char *dest, const char *src, int start, int n)
{
    if (!dest || !src || start < 0 || n <= 0)
        return NULL;
    strncpy(dest, src + start, n);
    dest[n] = '\0';
    return dest;
}

static char *create_new_line(char *line, struct idx_s *idx, char *var_value)
{
    int len = my_strlen(line) - idx->size + my_strlen(var_value);
    char *new_line = malloc(sizeof(char) * (len + 1));

    if (!new_line)
        return NULL;
    strncpy(new_line, line, idx->start);
    new_line[idx->start] = '\0';
    strcat(new_line, var_value);
    strcat(new_line, line + idx->end);
    return new_line;
}

static char *change_var(char *line, local_var_t *local_vars)
{
    struct idx_s idx = get_idx(line);
    char *var_value = NULL;
    char *var_name = NULL;
    char *new_line = NULL;

    if (idx.start == -1 || idx.end == -1 || idx.size <= 1)
        return line;
    var_name = malloc(sizeof(char) * (idx.size));
    if (!var_name)
        return line;
    strntncpy(var_name, line, idx.start + 1, idx.size - 1);
    var_value = get_var_value(local_vars, var_name);
    free(var_name);
    new_line = create_new_line(line, &idx, var_value);
    free(line);
    return new_line;
}

char *change_all_vars(char *line, local_var_t *local_vars)
{
    int counter = var_counter(line);
    char *new_line = line;

    if (counter == 0)
        return line;
    for (int i = 0; i <= counter; i++)
        new_line = change_var(new_line, local_vars);
    return new_line;
}
