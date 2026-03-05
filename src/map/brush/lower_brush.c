/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** lower_brush.c
*/

#include "my.h"

static void process_lower(game_t *game, sfVector2i *p, sfVector2i *c, float *st)
{
    float dist = 0;

    if (p->x < 0 || p->x >= game->map->width ||
        p->y < 0 || p->y >= game->map->height)
        return;
    dist = sqrt(pow(p->x - c->x, 2) + pow(p->y - c->y, 2));
    if (dist <= st[0])
        game->map->z_map[p->y][p->x] -= st[1];
}

void lower_brush(game_t *game, int center_x, int center_y)
{
    int rad = 1;
    float str = 1.0;
    sfVector2i p = {0, 0};
    sfVector2i c = {center_x, center_y};
    float st[2] = {0, 0};

    if (game->pl_ui->tb->brush->radius_pos > 0)
        rad = atoi(game->pl_ui->tb->brush->radius_input);
    if (game->pl_ui->tb->brush->strength_pos > 0)
        str = atof(game->pl_ui->tb->brush->strength_input);
    if (rad <= 0)
        rad = 1;
    if (str == 0)
        str = 1.0;
    st[0] = rad;
    st[1] = str;
    for (p.y = c.y - rad; p.y <= c.y + rad; p.y++) {
        for (p.x = c.x - rad; p.x <= c.x + rad; p.x++)
            process_lower(game, &p, &c, st);
    }
}
