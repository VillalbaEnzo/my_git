/*
** EPITECH PROJECT, 2026
** game_loop.c
** File description:
** game_loop.c
*/

#include "my.h"

static void change_grid(board_t *board, char to_put)
{
    board->grid[board->play_x + 1][board->play_y + 1] = to_put;
}

void after_play(board_t *board, int player)
{
    if (player == 1)
        change_grid(board, board->p1);
    if (player == 2)
        change_grid(board, board->p2);
}

void before_play(board_t *board, int *player)
{
    printf("Player %i>", *player);
    if (*player == 1)
        *player = 2;
    else
        *player = 1;
}

void game_loop(board_t *board)
{
    int player = 1;
    size_t len = 0;
    char *line = NULL;
    char **array;

    while (!is_end(board)){
        print_grid(board);
        before_play(board, &player);
        getline(&line, &len, stdin);
        array = my_str_to_word_array(line);
        board->play_x = atoi(array[0]);
        board->play_y = atoi(array[1]);
        if (board->play_x >= board->size_grid ||
            board->play_y >= board->size_grid ||
                board->grid[board->play_x][board->play_y] != ' '){
            printf("Wrong coordinates\n");
            continue;
        }
        after_play(board, player);
    }
    printf("je suis sortie\n");
}
