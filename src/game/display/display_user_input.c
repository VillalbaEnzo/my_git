/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** display_user_input.c
*/

#include "my.h"

void display_user_input(game_t *game)
{
    brush_t *br = game->pl_ui->tb->brush;
    ui_state_t pl_state = game->pl_ui->ui_state;
    game_state_t game_state = game->state;

    if (pl_state == SAVE) {
        sfRenderWindow_drawRectangleShape(game->window,
            game->pl_ui->input_box, NULL);
        sfRenderWindow_drawText(game->window, game->pl_ui->save_input, NULL);
        sfText_setString(game->pl_ui->save_input, game->pl_ui->input);
    }
    if (pl_state == INPUT_RADIUS || pl_state == INPUT_STRENGTH) {
        sfText_setString(br->radius_text, br->radius_input);
        sfText_setString(br->strength_text, br->strength_input);
    }
    if (game_state == LOADMAP) {
        sfText_setString(game->start_menu->load_input,
            game->start_menu->input);
        sfRenderWindow_drawRectangleShape(game->window,
            game->start_menu->input_box, NULL);
        sfRenderWindow_drawText(game->window,
            game->start_menu->load_input, NULL);
    }
}
