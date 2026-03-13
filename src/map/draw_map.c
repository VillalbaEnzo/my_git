/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** draw_map.c
*/

#include "my.h"

static sfRenderStates get_render_states(game_t *game, int i, int j)
{
    sfRenderStates temp = sfRenderStates_default();

    if (game->map->z_map[i][j] < 2.0)
        temp.texture = game->textures->dirt_text;
    if (2.0 < game->map->z_map[i][j] && game->map->z_map[i][j] < 6.0)
        temp.texture = game->textures->grass_text;
    if (6.0 < game->map->z_map[i][j] && game->map->z_map[i][j] < 9.0)
        temp.texture = game->textures->stone_text;
    if (9.0 < game->map->z_map[i][j] && game->map->z_map[i][j] < 17.0)
        temp.texture = game->textures->snow_text;
    if (17.0 < game->map->z_map[i][j])
        temp.texture = game->textures->secret_text;
    return temp;
}

static sfVertexArray *create_triangle(sfVector2f *point1,
    sfVector2f *point2, sfVector2f *point3, sfVector2f *point4)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};
    sfVertex vertex3 = {.position = *point3, .color = sfWhite};
    sfVertex vertex4 = {.position = *point4, .color = sfWhite};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_append(vertex_array, vertex4);
    sfVertexArray_setPrimitiveType(vertex_array, sfQuads);
    return vertex_array;
}

static sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_line = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfBlack};
    sfVertex vertex2 = {.position = *point2, .color = sfBlack};

    sfVertexArray_append(vertex_line, vertex1);
    sfVertexArray_append(vertex_line, vertex2);
    sfVertexArray_setPrimitiveType(vertex_line, sfLinesStrip);
    return vertex_line;
}

static void draw_border_lines(game_t *game, int i, int j, sfRenderStates *def)
{
    map_t *m = game->map;
    sfVertexArray *line1 = NULL;
    sfVertexArray *line2 = NULL;

    if (i == m->height - 1 && j != m->width - 1) {
        line1 = create_line(&m->points_2d[i][j], &m->points_2d[i][j + 1]);
        sfRenderWindow_drawVertexArray(game->window, line1, def);
        sfVertexArray_destroy(line1);
    }
    if (i != m->height - 1 && j == m->width - 1) {
        line2 = create_line(&m->points_2d[i][j], &m->points_2d[i + 1][j]);
        sfRenderWindow_drawVertexArray(game->window, line2, def);
        sfVertexArray_destroy(line2);
    }
}

static void draw_conditions(game_t *game, int i, int j)
{
    map_t *m = game->map;
    sfVertexArray *quad = NULL;
    sfVertexArray *line1 = NULL;
    sfVertexArray *line2 = NULL;
    sfRenderStates quad_render = get_render_states(game, i, j);
    sfRenderStates def_render = sfRenderStates_default();

    if (i < m->height - 1 && j < m->width - 1) {
        quad = create_triangle(&m->points_2d[i][j], &m->points_2d[i][j + 1],
            &m->points_2d[i + 1][j + 1], &m->points_2d[i + 1][j]);
        sfRenderWindow_drawVertexArray(game->window, quad, &quad_render);
        sfVertexArray_destroy(quad);
        line1 = create_line(&m->points_2d[i][j], &m->points_2d[i][j + 1]);
        sfRenderWindow_drawVertexArray(game->window, line1, &def_render);
        sfVertexArray_destroy(line1);
        line2 = create_line(&m->points_2d[i][j], &m->points_2d[i + 1][j]);
        sfRenderWindow_drawVertexArray(game->window, line2, &def_render);
        sfVertexArray_destroy(line2);
    }
    draw_border_lines(game, i, j, &def_render);
}

void draw_map(game_t *game)
{
    for (int i = 0; i < game->map->height; i++) {
        for (int j = 0; j < game->map->width; j++) {
            draw_conditions(game, i, j);
        }
    }
}
