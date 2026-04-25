/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_menu.c
*/

#include "wolf3d.h"
#include "textures_paths.h"
#include <stdlib.h>

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->bg_texture = sfTexture_createFromFile(MENU_BG, NULL);
    menu->bg_sprite = sfSprite_create();
    sfSprite_setTexture(menu->bg_sprite, menu->bg_texture, sfTrue);
    menu->cursor_texture = sfTexture_createFromFile(CURSOR, NULL);
    menu->cursor_sprite = sfSprite_create();
    sfSprite_setTexture(menu->cursor_sprite, menu->cursor_texture, sfTrue);
    menu->selected_btn = BTN_NEW_GAME;
    menu->cursor_positions[BTN_NEW_GAME] = (sfVector2f){300, 200};
    menu->cursor_positions[BTN_LOAD_GAME] = (sfVector2f){300, 300};
    menu->cursor_positions[BTN_SETTINGS] = (sfVector2f){300, 400};
    menu->cursor_positions[BTN_QUIT] = (sfVector2f){300, 500};
    sfSprite_setPosition(menu->cursor_sprite,
        menu->cursor_positions[menu->selected_btn]);
    return menu;
}
