/*
** EPITECH PROJECT, 2026
** tictactoe
** File description:
** descr
*/

#include "my.h"

static bool change_player_char(board_t *board, char *arg, int player)
{
    if (strlen(arg) > 1)
        return false;
    if (isalpha(arg[0]) == 0)
        return false;
    if (player == 1)
        board->p1 = arg[0];
    if (player == 2)
        board->p2 = arg[0];
    return true;
}

static bool change_grid_size(board_t *board, char *arg)
{
    int new_size = atoi(arg);

    for (int i = 0; arg[i]; i++)
        if (!isdigit(arg[i]))
            return false;
    if (new_size < 3)
        return false;
    board->size_grid = new_size;
    return true;
}

static bool handle_flags(board_t *board, char **args, int i)
{
    if (strcmp(args[i], "-p1") == 0) {
        if (!change_player_char(board, args[i + 1], 1))
            return false;
    }
    if (strcmp(args[i], "-p2") == 0)
        if (!change_player_char(board, args[i + 1], 2))
            return false;
    if (strcmp(args[i], "-s") == 0)
        if (!change_grid_size(board, args[i + 1]))
            return false;
    if ((strcmp(args[i], "-p1") != 0 && i % 2 == 1)
        && (strcmp(args[i], "-p2") != 0 && i % 2 == 1)
        && (strcmp(args[i], "-s") != 0 && i % 2 == 1))
        return false;
    return true;
}

bool parsing(board_t *board, char **args)
{
    for (int i = 0; args[i]; i++)
        if (!handle_flags(board, args, i))
            return false;
    printf("p1 : %c\np2 : %c\ngrid_size : %i\n", board->p1,
        board->p2, board->size_grid);
    return true;
}
