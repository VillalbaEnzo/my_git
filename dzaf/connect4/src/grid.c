/*
** EPITECH PROJECT, 2026
** grid.c
** File description:
** desc
*/

#include "my.h"

char **create_grid(board_t *board)
{
    char **tab = malloc(sizeof(char *) * (board->size_grid + 4));

    if (!tab)
        return NULL;
    tab[board->size_grid + 2] = NULL;
    for (int i = 0; i < board->size_grid + 3; i++) {
        tab[i] = malloc(sizeof(char) * (board->size_grid + 4));
        if (!tab[i])
            return NULL;
        tab[i][board->size_grid + 2] = '\0';
    }
    for (int i = 0; i < board->size_grid + 2; i++) {
        for (int j = 0; j < board->size_grid + 2; j++)
            tab[i][j] = ' ';
    }
    return tab;
}

void fill_grid(board_t *board)
{
    board->grid[0][0] = '*';
    for (int i = 1; i < board->size_grid + 1; i++) {
        board->grid[0][i] = '-';
        board->grid[board->size_grid + 1][i] = '-';
        board->grid[i][0] = '|';
        board->grid[i][board->size_grid + 1] = '|';
    }
    board->grid[0][board->size_grid + 1] = '*';
    board->grid[board->size_grid + 1][0] = '*';
    board->grid[board->size_grid + 1][board->size_grid + 1] = '*';
}

void print_grid(board_t *board)
{
    for (int i = 0; board->grid[i]; i++) {
        for (int j = 0; board->grid[i][j]; j++)
            write(1, &board->grid[i][j], 1);
        write(1, "\n", 1);
    }
}
