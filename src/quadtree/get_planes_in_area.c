/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** get_planes_in_area.c
*/

#include "../../include/my.h"
void get_planes_in_area(quadtree_t *node, sfFloatRect area,
    sprite_list_t **list, int *count);

static void search_in_children(quadtree_t *node, sfFloatRect area,
    sprite_list_t **list, int *count)
{
    int index = get_index(node, area);

    if (index != -1)
        get_planes_in_area(node->children[index], area, list, count);
    else {
        for (int i = 0; i < 4; i++)
            get_planes_in_area(node->children[i], area, list, count);
    }
}

void get_planes_in_area(quadtree_t *node, sfFloatRect area,
    sprite_list_t **list, int *count)
{
    if (!node)
        return;
    if (node->divided)
        search_in_children(node, area, list, count);
    for (int i = 0; i < node->nbr_plane; i++) {
        list[*count] = node->plane[i];
        *count += 1;
    }
}