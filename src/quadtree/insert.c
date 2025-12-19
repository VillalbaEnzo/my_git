/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** insert.c
*/

#include "../../include/my.h"

static void redistribute_planes(quadtree_t *node)
{
    int i = 0;
    int index = -1;
    sfFloatRect rect;

    while (i < node->nbr_plane) {
        rect = sfRectangleShape_getGlobalBounds(node->plane[i]->hitbox);
        index = get_index(node, &rect);
        if (index != -1) {
            insert(node->children[index], node->plane[i]);
            node->plane[i] = node->plane[node->nbr_plane - 1];
            node->nbr_plane--;
        } else {
            i++;
        }
    }
}

static bool insert_into_child(quadtree_t *node, sprite_list_t *plane,
    sfFloatRect *plane_rect)
{
    int index = -1;

    if (node->divided) {
        index = get_index(node, plane_rect);
        if (index != -1) {
            insert(node->children[index], plane);
            return true;
        }
    }
    return false;
}

void insert(quadtree_t *node, sprite_list_t *plane)
{
    sfFloatRect plane_rect;

    if (!plane || !plane->hitbox)
        return;
    plane_rect = sfRectangleShape_getGlobalBounds(plane->hitbox);
    if (!sfFloatRect_intersects(&node->zone, &plane_rect, NULL))
        return;
    if (insert_into_child(node, plane, &plane_rect))
        return;
    node->plane[node->nbr_plane] = plane;
    node->nbr_plane++;
    if (node->nbr_plane > CAPACITY && !node->divided) {
        split(node);
        redistribute_planes(node);
    }
}
