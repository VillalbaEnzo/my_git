/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** start_btn.c
*/

#include "my.h"

void handle_start_btn(game_t *game)
{
    if (!game->mouse_clicked)
        return;
    game->state = PLAYING;
    printf("start btn clicked\n");
    return;
}
