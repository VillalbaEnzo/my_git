/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** get_index.c
*/

#include "../../include/my.h"

int get_index(quadtree_t *node, sfFloatRect *rect)
{
    float mid_x = node->zone.left + (node->zone.width / 2);
    float mid_y = node->zone.top + (node->zone.height / 2);

    if (rect->left + rect->width < mid_x) {
        if (rect->top + rect->height < mid_y)
            return 0;
        if (rect->top > mid_y)
            return 2;
    }
    if (rect->left > mid_x) {
        if (rect->top + rect->height < mid_y)
            return 1;
        if (rect->top > mid_y)
            return 3;
    }
    return -1;
}
