/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** plane_tower.c
*/

#include "../../include/my.h"

static bool create_plane_requirement(sprite_list_t *plane)
{
    plane->texture = sfTexture_createFromFile("assets/images/plane.png", NULL);
    if (!plane->texture)
        return false;
    plane->sprite = sfSprite_create();
    if (!plane->sprite)
        return false;
    plane->hitbox = sfRectangleShape_create();
    if (!plane->hitbox)
        return false;
    return true;
}

static bool create_tower_requirement(sprite_list_t *tower)
{
    tower->texture = sfTexture_createFromFile("assets/images/tower.png", NULL);
    if (!tower->texture)
        return false;
    tower->sprite = sfSprite_create();
    if (!tower->sprite)
        return false;
    tower->area = sfCircleShape_create();
    if (!tower->area)
        return false;
    return true;
}

static bool create_plane(sprite_list_t *plane)
{
    sfVector2u size;

    if (!create_plane_requirement(plane))
        return false;
    sfSprite_setTexture(plane->sprite, plane->texture, sfTrue);
    sfSprite_setPosition(plane->sprite, plane->start_pos);
    sfSprite_scale(plane->sprite, (sfVector2f){PLANE_SCALE, PLANE_SCALE});
    size = sfTexture_getSize(plane->texture);
    sfSprite_setOrigin(plane->sprite, (sfVector2f){size.x / 2.0f,
            size.y / 2.0f});
    sfRectangleShape_setSize(plane->hitbox, (sfVector2f){20, 20});
    sfRectangleShape_setFillColor(plane->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(plane->hitbox, sfGreen);
    sfRectangleShape_setOutlineThickness(plane->hitbox, 1.0f);
    sfRectangleShape_setPosition(plane->hitbox, (sfVector2f){
            plane->start_pos.x - 10, plane->start_pos.y - 10});
    return true;
}

static bool create_tower(sprite_list_t *tower)
{
    sfVector2u size;

    if (!create_tower_requirement(tower))
        return false;
    sfSprite_setTexture(tower->sprite, tower->texture, sfTrue);
    sfSprite_scale(tower->sprite, (sfVector2f){TOWER_SCALE, TOWER_SCALE});
    size = sfTexture_getSize(tower->texture);
    sfSprite_setOrigin(tower->sprite, (sfVector2f){size.x / 2.0f,
            size.y / 2.0f});
    sfSprite_setPosition(tower->sprite, tower->start_pos);
    sfCircleShape_setRadius(tower->area, (float)tower->radius);
    sfCircleShape_setFillColor(tower->area, sfTransparent);
    sfCircleShape_setOutlineColor(tower->area, sfRed);
    sfCircleShape_setOutlineThickness(tower->area, 1.0f);
    sfCircleShape_setPosition(tower->area, (sfVector2f){
            tower->start_pos.x - tower->radius,
            tower->start_pos.y - tower->radius});
    return true;
}

void load_entities_resources(game_t *game)
{
    sprite_list_t *current = game->entities;

    while (current != NULL) {
        if (current->is_plane)
            create_plane(current);
        if (!current->is_plane)
            create_tower(current);
        current = current->next;
    }
}
