/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** load_map_from_file.c
*/

#include "my.h"

static void parse_file_data(game_t *game, FILE *file)
{
    int w = 0;
    int h = 0;

    if (fscanf(file, "%d %d", &w, &h) != 2)
        return;
    game->map->width = w;
    game->map->height = h;
    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++)
            fscanf(file, "%f", &game->map->z_map[y][x]);
    }
    update_2d_map(game);
    game->state = PLAYING;
}

void load_map_from_file(game_t *game)
{
    char *filename;
    FILE *file;

    if (!game->start_menu->input || strlen(game->start_menu->input) == 0)
        return;
    filename = get_legend_name(game->start_menu->input);
    if (!filename)
        return;
    file = fopen(filename, "r");
    if (file) {
        parse_file_data(game, file);
        fclose(file);
    }
    free(filename);
}
