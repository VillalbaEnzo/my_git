/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** smooth_brush.c
*/

#include "my.h"

static void acc_smooth(game_t *game, sfVector2i *p, sfVector2i *c, float *st)
{
    float dist = 0;

    if (p->x < 0 || p->x >= game->map->width ||
        p->y < 0 || p->y >= game->map->height)
        return;
    dist = sqrt(pow(p->x - c->x, 2) + pow(p->y - c->y, 2));
    if (dist <= st[0]) {
        st[1] += game->map->z_map[p->y][p->x];
        st[2] += 1;
    }
}

static void apply_s(game_t *game, sfVector2i *p, sfVector2i *c, float *st)
{
    float dist = 0;
    float diff = 0;

    if (p->x < 0 || p->x >= game->map->width ||
        p->y < 0 || p->y >= game->map->height)
        return;
    dist = sqrt(pow(p->x - c->x, 2) + pow(p->y - c->y, 2));
    if (dist <= st[0]) {
        diff = st[2] - game->map->z_map[p->y][p->x];
        game->map->z_map[p->y][p->x] += diff * st[1];
    }
}

static void apply_smooth_loop(game_t *game, sfVector2i *c, float *st_app)
{
    sfVector2i p = {0, 0};
    int rad = st_app[0];

    for (p.y = c->y - rad; p.y <= c->y + rad; p.y++) {
        for (p.x = c->x - rad; p.x <= c->x + rad; p.x++)
            apply_s(game, &p, c, st_app);
    }
}

static void init_smooth(game_t *game, int *r, float *str)
{
    if (game->pl_ui->tb->brush->radius_pos > 0)
        *r = atoi(game->pl_ui->tb->brush->radius_input);
    if (game->pl_ui->tb->brush->strength_pos > 0)
        *str = atof(game->pl_ui->tb->brush->strength_input);
    if (*r <= 0)
        *r = 1;
    if (*str <= 0)
        *str = 50.0;
    if (*str > 1.0)
        *str = *str / 100.0;
    *str = *str * 0.05;
}

void smooth_brush(game_t *game, int center_x, int center_y)
{
    int r = 1;
    float str = 0.5;
    sfVector2i p = {0, 0};
    sfVector2i c = {center_x, center_y};
    float st[3] = {0, 0, 0};
    float app[3] = {0, 0, 0};

    init_smooth(game, &r, &str);
    st[0] = r;
    for (p.y = c.y - r; p.y <= c.y + r; p.y++) {
        for (p.x = c.x - r; p.x <= c.x + r; p.x++)
            acc_smooth(game, &p, &c, st);
    }
    if (st[2] == 0)
        return;
    app[0] = r;
    app[1] = str;
    app[2] = st[1] / st[2];
    apply_smooth_loop(game, &c, app);
}
