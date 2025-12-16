/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** free_sprite_node.c
*/

#include "../../include/my.h"

void free_sprite_node(sprite_list_t *node)
{
    if (!node)
        return;
    if (node->sprite)
        sfSprite_destroy(node->sprite);
    if (node->texture)
        sfTexture_destroy(node->texture);
    if (node->hitbox)
        sfRectangleShape_destroy(node->hitbox);
    if (node->area)
        sfCircleShape_destroy(node->area);
    free(node);
}
