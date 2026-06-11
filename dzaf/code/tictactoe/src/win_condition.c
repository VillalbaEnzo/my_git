/*
** EPITECH PROJECT, 2026
** win_condition.c
** File description:
** win_condition.c
*/

#include "my.h"

static bool check_top_left(char **grid, int x, int y)
{
    if (grid[x][y] == grid[x + 1][y + 1] && grid[x][y] == grid[x + 2][y + 2])
        return true;
    return false;
}

static bool check_top_right(char **grid, int x, int y)
{
    if (grid[x][y] == grid[x - 1][y - 1] && grid[x][y] == grid[x - 2][y - 2])
        return true;
    return false;
}

static bool check_line(char **grid, int x, int y)
{
    if (grid[x][y] == grid[x][y + 1] && grid[x][y] == grid[x][y + 2])
        return true;
    return false;
}

static bool check_column(char **grid, int x, int y)
{
    if (grid[x][y] == grid[x + 1][y] && grid[x][y] == grid[x + 2][y])
        return true;
    return false;
}

static void print_win(char winner, board_t *board)
{
    if (winner == board->p1)
        printf("Player 1 won!\n");
    if (winner == board->p2)
        printf("Player 2 won!\n");
}

int check_draw(char pawn)
{
    if (pawn == ' ')
        return 1;
    return 0;
}

bool is_draw(board_t *board)
{
    int verif_draw = 0;

    for (int x = 1; x <= board->size_grid; x++){
        for (int y = 1; y <= board->size_grid; y++)
            verif_draw += check_draw(board->grid[x][y]);
    }
    if (verif_draw == 0){
        printf("Draw!\n");
        return true;
    }
    return false;
}

bool check_crossline_win(board_t *board)
{
    if (check_top_left(board->grid, 1, 1)){
        print_win(board->grid[1][1], board);
        return true;
    }
    if (check_top_right(board->grid, 1, board->size_grid)){
        print_win(board->grid[1][board->size_grid], board);
        return true;
    }
    return false;
}

bool is_end(board_t *board)
{
    if (board->curr_round < board->size_grid)
        return false;
    for (int y = 1; y <= board->size_grid; y++){
        if (check_column(board->grid, 1, y)){
            print_win(board->grid[1][y], board);
            return true;
        }
    }
    for (int x = 1; x <= board->size_grid; x++){
        if (check_column(board->grid, x, 1)){
            print_win(board->grid[x][1], board);
            return true;
        }
    }
    if (check_crossline_win(board))
        return true;
    return is_draw(board);
}
