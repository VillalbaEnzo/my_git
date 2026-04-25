/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** display_page.c
*/

#include "wolf3d.h"
#include "structs.h"

void display_menu(game_t *game)
{
    sfRenderWindow_drawSprite(game->window->render,
        game->ui->menu->bg_sprite, NULL);
    sfRenderWindow_drawSprite(game->window->render,
        game->ui->menu->cursor_sprite, NULL);
}
