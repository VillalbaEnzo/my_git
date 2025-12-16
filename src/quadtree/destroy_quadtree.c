/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** destroy_quadtree.c
*/

#include "../../include/my.h"

void destroy_quadtree(quadtree_t *node)
{
    if (!node)
        return;
    if (node->divided) {
        for (int i = 0; i < 4; i++)
            destroy_quadtree(node->children[i]);
    }
    free(node);
}
