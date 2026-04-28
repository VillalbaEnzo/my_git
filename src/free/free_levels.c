/*
** EPITECH PROJECT, 2026
** free_levels.c
** File description:
** free_levels
*/

#include "wolf3d.h"

void free_level(level_t *level)
{
    if (!level)
        return;
    if (level->map) {
        for (int y = 0; y < level->map->height; y++)
            free(level->map->grid[y] ? : NULL);
        free(level->map->grid ? : NULL);
        free(level->map);
    }
    free(level->name ? : NULL);
    free(level);
}

void free_levels(level_t **levels)
{
    if (!levels)
        return;
    for (int i = 0; levels[i]; i++)
        free_level(levels[i]? : NULL);
    free(levels);
}
