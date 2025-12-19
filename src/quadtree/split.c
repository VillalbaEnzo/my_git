/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** split.c
*/

#include "../../include/my.h"

void split(quadtree_t *node)
{
    float new_w = node->zone.width / 2;
    float new_h = node->zone.height / 2;
    float x = node->zone.left;
    float y = node->zone.top;
    sfFloatRect zone0 = {x, y, new_w, new_h};
    sfFloatRect zone1 = {x + new_w, y, new_w, new_h};
    sfFloatRect zone2 = {x, y + new_h, new_w, new_h};
    sfFloatRect zone3 = {x + new_w, y + new_h, new_w, new_h};

    node->children[0] = create_quadtree(&zone0);
    node->children[1] = create_quadtree(&zone1);
    node->children[2] = create_quadtree(&zone2);
    node->children[3] = create_quadtree(&zone3);
    node->divided = true;
}
