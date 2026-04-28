/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5
** File description:
** render.c
*/

#include "wolf3d.h"

static void draw_column(game_t *game, col_params_t *p)
{
    sfRectangleShape *col = game->render_col;
    sfVector2f size = {1.0f, (float)(p->bot - p->top)};
    sfVector2f pos = {(float)p->x, (float)p->top};

    sfRectangleShape_setSize(col, size);
    sfRectangleShape_setPosition(col, pos);
    sfRectangleShape_setFillColor(col, *p->color);
    sfRenderWindow_drawRectangleShape(game->window->render, col, NULL);
}

static sfColor get_wall_color(int side, int map_val)
{
    (void)map_val;
    if (side == 1)
        return sfColor_fromRGB(150, 0, 0);
    return sfColor_fromRGB(220, 0, 0);
}

static void clamp_line(int *top, int *bot)
{
    if (*top < 0)
        *top = 0;
    if (*bot >= SCREEN_H)
        *bot = SCREEN_H - 1;
}

static void init_ray_steps(player_t *p, ray_t *r)
{
    if (r->dx < 0) {
        r->step_x = -1;
        r->side_x = (p->pos.x - r->map_x) * r->delta_x;
    } else {
        r->step_x = 1;
        r->side_x = (r->map_x + 1.0 - p->pos.x) * r->delta_x;
    }
    if (r->dy < 0) {
        r->step_y = -1;
        r->side_y = (p->pos.y - r->map_y) * r->delta_y;
    } else {
        r->step_y = 1;
        r->side_y = (r->map_y + 1.0 - p->pos.y) * r->delta_y;
    }
}

static void dda_step(ray_t *r)
{
    if (r->side_x < r->side_y) {
        r->side_x += r->delta_x;
        r->map_x += r->step_x;
        r->side = 0;
    } else {
        r->side_y += r->delta_y;
        r->map_y += r->step_y;
        r->side = 1;
    }
}

static void run_dda(map_t *map, ray_t *r)
{
    while (!r->hit) {
        dda_step(r);
        if (map->grid[r->map_y][r->map_x] > 0)
            r->hit = 1;
    }
}

static void draw_wall_column(game_t *game, map_t *map, ray_t *r, int x)
{
    col_params_t params;
    sfColor color;
    double wall_dist;
    int line_h;
    int top;
    int bot;

    if (r->side == 0)
        wall_dist = r->side_x - r->delta_x;
    else
        wall_dist = r->side_y - r->delta_y;
    line_h = (int)(SCREEN_H / wall_dist);
    top = -line_h / 2 + SCREEN_H / 2;
    bot = line_h / 2 + SCREEN_H / 2;
    clamp_line(&top, &bot);
    color = get_wall_color(r->side, map->grid[r->map_y][r->map_x]);
    params = (col_params_t){x, top, bot, &color};
    draw_column(game, &params);
}

static void cast_ray(game_t *game, map_t *map, ray_t *r, int x)
{
    run_dda(map, r);
    draw_wall_column(game, map, r, x);
}

static void render_raycasting(game_t *game, map_t *map)
{
    player_t *p = game->player;
    ray_t r;

    for (int x = 0; x < SCREEN_W; x++) {
        r.cam_x = 2.0 * x / (double)SCREEN_W - 1.0;
        r.dx = p->dir.x + p->plane.x * r.cam_x;
        r.dy = p->dir.y + p->plane.y * r.cam_x;
        r.map_x = (int)p->pos.x;
        r.map_y = (int)p->pos.y;
        r.delta_x = (r.dx == 0) ? 1e30 : fabs(1.0 / r.dx);
        r.delta_y = (r.dy == 0) ? 1e30 : fabs(1.0 / r.dy);
        r.hit = 0;
        init_ray_steps(p, &r);
        cast_ray(game, map, &r, x);
    }
}

void render(game_t *game, map_t *map)
{
    sfColor ceil_col = sfColor_fromRGB(50, 50, 50);
    sfColor floor_col = sfColor_fromRGB(100, 100, 100);
    sfRectangleShape *half = game->render_half;
    sfVector2f size = {SCREEN_W, SCREEN_H / 2};
    sfVector2f pos_ceil = {0, 0};
    sfVector2f pos_floor = {0, SCREEN_H / 2};

    sfRectangleShape_setSize(half, size);
    sfRectangleShape_setFillColor(half, ceil_col);
    sfRectangleShape_setPosition(half, pos_ceil);
    sfRenderWindow_drawRectangleShape(game->window->render, half, NULL);
    sfRectangleShape_setFillColor(half, floor_col);
    sfRectangleShape_setPosition(half, pos_floor);
    sfRenderWindow_drawRectangleShape(game->window->render, half, NULL);
    render_raycasting(game, map);
}
