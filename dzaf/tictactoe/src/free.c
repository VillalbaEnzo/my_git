/*
** EPITECH PROJECT, 2026
** free.c
** File description:
** free.c
*/

#include "my.h"

int free_and_return(board_t *board, int ret)
{
    if (!board)
        return ret;
    for (int x = 0; x < board->size_grid; x++){
        if (board->grid[x])
            free(board->grid[x]);
    }
    if (board->grid)
        free(board->grid);
    free(board);
    return ret;
}
