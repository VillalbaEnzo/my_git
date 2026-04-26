/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** handle_menu.c
*/

#include "structs.h"
#include "wolf3d.h"
#include "paths.h"

void execute_menu_action(game_t *game)
{
    switch (game->ui->menu->selected_btn) {
        case BTN_NEW_GAME:
            game->state = STATE_PLAY;
            break;
        case BTN_LOAD_GAME:
            break;
        case BTN_SETTINGS:
            game->state = STATE_SETTINGS;
            break;
        case BTN_QUIT:
            sfRenderWindow_close(game->window->render);
            break;
    }
}

void handle_menu(game_t *game)
{
    for (int i = 0; i < BTN_COUNT; i++) {
        if (game->ui->menu->selected_btn == i)
            sfText_setColor(game->ui->menu->btn_texts[i], sfBlue);
        else sfText_setColor(game->ui->menu->btn_texts[i], sfWhite);
    }
    display_menu(game);
}
