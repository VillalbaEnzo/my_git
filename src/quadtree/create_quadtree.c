/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** create_quadtree.c
*/

#include "../../include/my.h"

quadtree_t *create_quadtree(sfFloatRect zone)
{
    quadtree_t *node = malloc(sizeof(quadtree_t));

    node->zone = zone;
    node->nbr_plane = 0;
    node->divided = false;
    for (int i = 0; i < 4; i++)
        node->children[i] = NULL;
    return node;
}
