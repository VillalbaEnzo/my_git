/*
** EPITECH PROJECT, 2026
** myworld [WSL: Ubuntu]
** File description:
** create_save_btn
*/
#include "my.h"

bool create_input_box(game_t *game)
{
    game->pl_ui->input_box = sfRectangleShape_create();
    if (!game->pl_ui->input_box)
        return false;
    sfRectangleShape_setFillColor(game->pl_ui->input_box, sfWhite);
    sfRectangleShape_setOutlineColor(game->pl_ui->input_box, sfBlack);
    sfRectangleShape_setSize(game->pl_ui->input_box, (sfVector2f){600, 30});
    sfRectangleShape_setPosition(game->pl_ui->input_box, (sfVector2f){240, 20});
    return true;
}

bool create_input_text(game_t *game)
{
    game->pl_ui->save_input = sfText_create();
    game->pl_ui->input = malloc(sizeof(char) * 21);
    if (!game->pl_ui->save_input || !game->pl_ui->input)
        return false;
    game->pl_ui->input[0] = '\0';
    sfText_setString(game->pl_ui->save_input, game->pl_ui->input);
    sfText_setFont(game->pl_ui->save_input, game->font);
    sfText_setCharacterSize(game->pl_ui->save_input, 30);
    sfText_setColor(game->pl_ui->save_input, sfBlack);
    sfText_setPosition(game->pl_ui->save_input, (sfVector2f){241, 20});
    return true;
}

bool create_save_btn(game_t *game)
{
    if (!create_input_box(game) || !create_input_text(game))
        return false;
    game->pl_ui->save_btn = sfText_create();
    if (!game->pl_ui->save_btn)
        return false;
    sfText_setString(game->pl_ui->save_btn, "Save");
    sfText_setFont(game->pl_ui->save_btn, game->font);
    sfText_setCharacterSize(game->pl_ui->save_btn, 30);
    sfText_setPosition(game->pl_ui->save_btn, (sfVector2f){135, 20});
    game->pl_ui->input_pos = 0;
    return true;
}
