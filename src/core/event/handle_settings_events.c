/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** handle_menu_events.c
*/

#include "structs.h"
#include "wolf3d.h"

static void execute_settings_action(game_t *game)
{
    sfSound_play(game->ui->sfx[SFX_MENU_CLICK]->sfx);
    switch (game->ui->settings->selected_btn) {
        case SET_MUSIC:
            break;
        case SET_SFX:
            break;
        case SET_RESIZE:
            game->state = STATE_SETTINGS;
            break;
        case SET_BACK:
            game->state = STATE_MENU;
            break;
    }
}

void handle_settings_events(game_t *game, sfEvent event)
{
    settings_t *set = game->ui->settings;
    ui_t *ui = game->ui;

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyDown) {
            set->selected_btn = (set->selected_btn + 1) % BTN_COUNT;
            sfSound_play(ui->sfx[SFX_MENU_SWITCH]->sfx);
        }
        if (event.key.code == sfKeyUp) {
            set->selected_btn = (set->selected_btn - 1 + BTN_COUNT)
                % BTN_COUNT;
            sfSound_play(ui->sfx[SFX_MENU_SWITCH]->sfx);
        }
        if (event.key.code == sfKeyEnter)
            execute_settings_action(game);
        sfSprite_setPosition(set->cursor_sprite,
            set->cursor_positions[set->selected_btn]);
    }
    if (event.type == sfEvtMouseButtonPressed)
        execute_settings_action(game);
}
