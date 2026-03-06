/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** save_map_to_file.c
*/

#include "my.h"

static void print_in_file(game_t *game, FILE *file)
{
    fprintf(file, "%d %d\n", game->map->width, game->map->height);
    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            fprintf(file, "%f ", game->map->z_map[y][x]);
        }
        fprintf(file, "\n");
    }
}

void save_map_to_file(game_t *game)
{
    char *filename;
    FILE *file;

    if (game->pl_ui->input == NULL || strlen(game->pl_ui->input) == 0)
        return;
    filename = get_legend_name(game->pl_ui->input);
    if (!filename)
        return;
    file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return;
    }
    print_in_file(game, file);
    fclose(file);
    free(filename);
}
