/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** parsing.c
*/

#include "my.h"

static bool check_line(char *line)
{
    int counter = 0;

    if (!line || !line[0] || line[0] == '#')
        return false;
    for (int i = 0; line[i]; i++) {
        if (line[i] == ';')
            counter++;
    }
    if (counter != 4)
        return false;
    return true;
}

static bool check_nbr(char *nbr)
{
    for (int i = 0; nbr[i]; i++) {
        if (!isdigit(nbr[i]))
            return false;
    }
    return true;
}

static bool check_arg(char **arg)
{
    int counter = 0;

    if (!arg || !arg[0])
        return false;
    for (; arg[counter]; counter++);
    if (counter != 5)
        return false;
    for (int i = 1; arg[i]; i++) {
        if (!check_nbr(arg[i]))
            return false;
    }
    return true;
}

static bool parsing_line(char *line, pokemon_t **head)
{
    pokemon_t *new_node = NULL;
    char **arg = NULL;

    if (!check_line(line))
        return false;
    arg = str_to_word_array(line, ";\n");
    if (!check_arg(arg)) {
        free_double_array(arg);
        return false;
    }
    new_node = create_node(*head, arg);
    free_double_array(arg);
    if (!new_node)
        return false;
    *head = new_node;
    return true;
}

static bool load_files(char *file_path, pokemon_t **head)
{
    FILE *file = fopen(file_path, "r");
    char *line = NULL;
    size_t len = 0;

    if (!file)
        return false;
    while (getline(&line, &len, file) != -1) {
        if (!parsing_line(line, head))
            continue;
    }
    free(line);
    fclose(file);
    return true;
}

static bool skip_dot(char *name)
{
    if (strcmp(name, ".") == 0 ||
        strcmp(name, "..") == 0)
        return true;
    return false;
}

bool parse_folder(char *folder_path, pokemon_t **head)
{
    DIR *dir = opendir(folder_path);
    struct dirent *entry;
    char *file_path = NULL;

    if (!dir)
        return false;
    entry = readdir(dir);
    while (entry) {
        if (skip_dot(entry->d_name)) {
            entry = readdir(dir);
            continue;
        }
        file_path = malloc(strlen(folder_path) + strlen(entry->d_name) + 2);
        sprintf(file_path, "%s/%s", folder_path, entry->d_name);
        load_files(file_path, head);
        free(file_path);
        entry = readdir(dir);
    }
    closedir(dir);
    return true;
}
