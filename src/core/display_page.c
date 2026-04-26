/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** display_page.c
*/

#include "wolf3d.h"
#include "structs.h"

static void display_menu(game_t *game)
{
    sfColor grey = sfColor_fromRGB(181, 181, 181);

    sfRenderWindow_drawSprite(game->window->render,
        game->ui->menu->bg_sprite, NULL);
    for (int i = 0; i < BTN_COUNT; i++) {
        sfRenderWindow_drawText(game->window->render,
            game->ui->menu->btn_texts[i], NULL);
        if (game->ui->menu->selected_btn == i)
            sfText_setColor(game->ui->menu->btn_texts[i], grey);
        else sfText_setColor(game->ui->menu->btn_texts[i], sfWhite);
    }
    sfRenderWindow_drawSprite(game->window->render,
        game->ui->menu->cursor_sprite, NULL);
}

void display_page(game_t *game)
{
    for (int i = 0; i < STATE_COUNT; i++) {
        switch (i) {
            case STATE_MENU:
                display_menu(game);
                break;
            default:
                break;
        }
    }
}
