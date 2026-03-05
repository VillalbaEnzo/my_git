/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** draw_map.c
*/

#include "my.h"

static sfVertexArray *create_line(game_t *game, sfVector2f *point1,
    sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};
    sfRenderStates def = sfRenderStates_default();

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLinesStrip);
    sfRenderWindow_drawVertexArray(game->window, vertex_array, &def);
    sfVertexArray_destroy(vertex_array);
    return vertex_array;
}

static void draw_conditions(game_t *game, int i, int j)
{
    map_t *m = game->map;

    if (i == m->height - 1 && j == m->width - 1)
        return;
    if (i == m->height - 1) {
        create_line(game, &m->points_2d[i][j], &m->points_2d[i][j + 1]);
        return;
    }
    if (j == m->width - 1) {
        create_line(game, &m->points_2d[i][j], &m->points_2d[i + 1][j]);
        return;
    }
    create_line(game, &m->points_2d[i][j], &m->points_2d[i][j + 1]);
    create_line(game, &m->points_2d[i][j], &m->points_2d[i + 1][j]);
}

void draw_map(game_t *game)
{
    for (int i = 0; i < game->map->height; i++) {
        for (int j = 0; j < game->map->width; j++) {
            draw_conditions(game, i, j);
        }
    }
}
