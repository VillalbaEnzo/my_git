/*
** EPITECH PROJECT, 2026
** myworld [WSL: Ubuntu]
** File description:
** get_user_input
*/

#include "my.h"

void display_user_input(game_t *game)
{
    if (game->pl_ui->ui_state == SAVE) {
        sfRenderWindow_drawRectangleShape(game->window,
            game->pl_ui->input_box, NULL);
        sfRenderWindow_drawText(game->window, game->pl_ui->save_input, NULL);
        sfText_setString(game->pl_ui->save_input, game->pl_ui->input);
    }
    if (game->pl_ui->ui_state == INPUT_RADIUS || game->pl_ui->ui_state == INPUT_STRENGTH) {
        sfText_setString(game->pl_ui->tb->brush->radius_text, game->pl_ui->tb->brush->radius_input);
        sfText_setString(game->pl_ui->tb->brush->strength_text, game->pl_ui->tb->brush->strength_input);
    }
}
