/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_start_btn.c
*/
#include "my.h"

bool create_start_btn(game_t *game)
{
    game->start_menu->start_btn->rect = sfRectangleShape_create();
    if (!game->start_menu->start_btn->rect)
        return false;
    game->start_menu->start_btn->texture = sfTexture_createFromFile(START_BTN,
        NULL);
    if (!game->start_menu->start_btn->texture)
        return false;
    sfRectangleShape_setTexture(game->start_menu->start_btn->rect,
        game->start_menu->start_btn->texture, sfTrue);
    return true;
}
