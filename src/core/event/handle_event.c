/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** handle_event.c
*/

#include "structs.h"
#include "wolf3d.h"

static void execute_menu_action(game_t *game)
{
    switch (game->ui->menu->selected_btn) {
        case BTN_NEW_GAME:
            game->state = STATE_PLAY;
            break;
        case BTN_LOAD_GAME:
            break;
        case BTN_SETTINGS:
            game->state = STATE_SETTINGS;
            break;
        case BTN_QUIT:
            sfRenderWindow_close(game->window->render);
            break;
    }
}

static void handle_menu_events(game_t *game, sfEvent event)
{
    menu_t *menu = game->ui->menu;

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyDown)
            menu->selected_btn = (menu->selected_btn + 1) % BTN_COUNT;
        if (event.key.code == sfKeyUp)
            menu->selected_btn = (menu->selected_btn - 1 + BTN_COUNT)
                % BTN_COUNT;
        if (event.key.code == sfKeyEnter)
            execute_menu_action(game);
        sfSprite_setPosition(menu->cursor_sprite,
            menu->cursor_positions[menu->selected_btn]);
    }
    if (event.type == sfEvtMouseButtonPressed)
        execute_menu_action(game);
}

void handle_events(game_t *game)
{
    sfEvent event = game->window->event;

    while (sfRenderWindow_pollEvent(game->window->render, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->window->render);
        if (game->state == STATE_MENU)
            handle_menu_events(game, game->window->event);
    }
}
