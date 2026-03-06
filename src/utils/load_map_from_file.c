/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** load_map_from_file.c
*/

#include "my.h"

void load_map_from_file(game_t *game)
{
    char *filename;
    int new_width = 0;
    int new_height = 0;
    FILE *file;

    if (game->pl_ui->input == NULL || strlen(game->pl_ui->input) == 0)
        return;
    filename = get_legend_name(game->pl_ui->input);
    if (!filename)
        return;
    file = fopen(filename, "r");
    if (file == NULL) {
        free(filename);
        return;
    }
    if (fscanf(file, "%d %d", &new_width, &new_height) != 2) {
        fclose(file);
        free(filename);
        return;
    }
    game->map->width = new_width;
    game->map->height = new_height;
    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++)
            fscanf(file, "%f", &game->map->z_map[y][x]);
    }
    fclose(file);
    free(filename);
    update_2d_map(game);
    game->state = PLAYING;
}
