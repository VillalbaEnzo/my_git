/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_quit_btn.c
*/

#include "my.h"

bool create_quit_btn(game_t *game)
{
    sfVector2f size = {300, 70};
    sfVector2f pos = {810, 625};

    game->start_menu->quit_btn->rect = sfRectangleShape_create();
    if (!game->start_menu->quit_btn->rect)
        return false;
    sfRectangleShape_setSize(game->start_menu->quit_btn->rect, size);
    sfRectangleShape_setPosition(game->start_menu->quit_btn->rect, pos);
    game->start_menu->quit_btn->texture = sfTexture_createFromFile(QUIT_BTN,
        NULL);
    if (!game->start_menu->quit_btn->texture)
        return false;
    sfRectangleShape_setTexture(game->start_menu->quit_btn->rect,
        game->start_menu->quit_btn->texture, sfTrue);
    sfRectangleShape_setOutlineColor(game->start_menu->quit_btn->rect,
        sfRed);
    return true;
}
