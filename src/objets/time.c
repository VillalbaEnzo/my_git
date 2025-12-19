/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** time.c
*/

#include "../../include/my.h"

bool create_time_text(game_t *game)
{
    sfVector2f view_size;
    sfVector2f position;
    sfFloatRect bounds;

    game->time_text->text = sfText_create();
    if (!game->time_text->text)
        return false;
    game->time_text->font =
        sfFont_createFromFile("assets/font/BRLNSDB.TTF");
    if (!game->time_text->font)
        return false;
    sfText_setFont(game->time_text->text, game->time_text->font);
    sfText_setCharacterSize(game->time_text->text, 35);
    sfText_setString(game->time_text->text, "00:00");
    view_size = sfView_getSize(sfRenderWindow_getView(game->window));
    bounds = sfText_getLocalBounds(game->time_text->text);
    position.x = view_size.x - bounds.width - 20;
    position.y = 20;
    sfText_setPosition(game->time_text->text, position);
    return true;
}
