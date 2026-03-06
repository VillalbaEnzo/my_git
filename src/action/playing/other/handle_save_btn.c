/*
** EPITECH PROJECT, 2026
** myworld [WSL: Ubuntu]
** File description:
** handle_save_btn
*/

#include "my.h"

void handle_save_btn(game_t *game)
{
    if (!game->mouse_clicked)
        return;
    sfText_setFillColor(game->pl_ui->save_btn, sfGreen);
    game->pl_ui->ui_state = SAVE;
}
