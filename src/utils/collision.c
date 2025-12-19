/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** collision.c
*/

#include "../../include/my.h"

static sfVector2f get_global_bound(sfFloatRect *plane_bounds)
{
    sfVector2f plane_center = {plane_bounds->left + plane_bounds->width / 2.0f,
        plane_bounds->top + plane_bounds->height / 2.0f};

    return plane_center;
}

static bool is_in_tower_area(sprite_list_t *plane, sprite_list_t *all_entities)
{
    sprite_list_t *tmp = all_entities;
    sfFloatRect plane_bounds = sfRectangleShape_getGlobalBounds(plane->hitbox);
    sfVector2f plane_center = get_global_bound(&plane_bounds);
    float radius = 0.0;
    float dx = 0.0;
    float dy = 0.0;
    sfVector2f tower_pos;

    while (tmp) {
        if (!tmp->is_plane) {
            tower_pos = tmp->start_pos;
            radius = (float)tmp->radius;
            dx = plane_center.x - tower_pos.x;
            dy = plane_center.y - tower_pos.y;
        }
        if (!tmp->is_plane && ((dx * dx + dy * dy) <= (radius * radius)))
            return true;
        tmp = tmp->next;
    }
    return false;
}

static void check_intersects(const sfFloatRect *area, sfFloatRect *other_box,
    sprite_list_t *plane, sprite_list_t *other)
{
    if (sfFloatRect_intersects(area, other_box, NULL)) {
        plane->is_destroyed = true;
        other->is_destroyed = true;
    }
}

static void check_collision_for_entity(quadtree_t *qt, sprite_list_t *plane)
{
    sprite_list_t *nearby[2048];
    int count = 0;
    sfFloatRect area = sfRectangleShape_getGlobalBounds(plane->hitbox);
    sprite_list_t *other;
    sfFloatRect other_box;

    get_planes_in_area(qt, &area, nearby, &count);
    for (int i = 0; i < count; i++) {
        other = nearby[i];
        if (plane != other && other->is_plane && other->has_taken_off &&
            !other->has_arrived && !other->is_destroyed) {
            other_box = sfRectangleShape_getGlobalBounds(other->hitbox);
            check_intersects(&area, &other_box, plane, other);
        }
    }
}

void check_collision(game_t *game)
{
    sfFloatRect screen = {0, 0, 1920, 1080};
    quadtree_t *qt = create_quadtree(&screen);
    sprite_list_t *tmp = game->entities;

    while (tmp) {
        if (tmp->is_plane && tmp->has_taken_off && !tmp->has_arrived &&
            !tmp->is_destroyed && tmp->hitbox) {
            insert(qt, tmp);
        }
        tmp = tmp->next;
    }
    tmp = game->entities;
    while (tmp) {
        if ((tmp->is_plane && tmp->has_taken_off && !tmp->has_arrived &&
                !tmp->is_destroyed && tmp->hitbox) &&
            !is_in_tower_area(tmp, game->entities))
            check_collision_for_entity(qt, tmp);
        tmp = tmp->next;
    }
    destroy_quadtree(qt);
}
