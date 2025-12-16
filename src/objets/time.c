/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** time.c
*/

#include "../../include/my.h"

bool create_time_text(game_t *game)
{
    sfVector2f position = {1850.0, 0.0};

    game->time_text->text = sfText_create();
    if (!game->time_text->text)
        return false;
    game->time_text->font = sfFont_createFromFile("assets/font/BRLNSDB.TTF");
    if (!game->time_text->font)
        return false;
    sfText_setFont(game->time_text->text, game->time_text->font);
    sfText_setCharacterSize(game->time_text->text, 35);
    sfText_setPosition(game->time_text->text, position);
    return true;
}
