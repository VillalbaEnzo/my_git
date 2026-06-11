/*
** EPITECH PROJECT, 2026
** tictactoe
** File description:
** desc
*/

#include "my.h"

board_t *init_board(void)
{
    board_t *board = malloc(sizeof(board_t));

    if (!board)
        return NULL;
    board->play_x = 0;
    board->play_y = 0;
    board->grid = NULL;
    board->curr_round = 0;
    board->p1 = 'X';
    board->p2 = 'O';
    board->size_grid = 3;
    return board;
}
