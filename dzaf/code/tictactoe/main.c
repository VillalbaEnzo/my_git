/*
** EPITECH PROJECT, 2025
** Duo Stumper
** File description:
** main.c
*/

#include "my.h"

int main(int argc, char **argv)
{
    int t1 = 0;
    int t2 = 0;
    board_t *board = init_board();

    if (!board)
        return 84;
    if (argc > 7 || (argc - 1) % 2 != 0)
        return 84;
    if (!parsing(board, argv))
        free_and_return(board, 84);
    board->grid = create_grid(board);
    fill_grid(board);
    game_loop(board);
    return free_and_return(board, 0);
}
