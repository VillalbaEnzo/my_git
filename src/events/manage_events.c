/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** manage_events.c
*/

#include "my.h"

static void close_window(game_t *game, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(game->window);
}

static void get_mouse_clicked(game_t *game, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        game->mouse_clicked = true;
    }
}

static void add_char(game_t *game, sfEvent event)
{
    if (game->pl_ui->input_pos == 20)
        return;
    game->pl_ui->input[game->pl_ui->input_pos] = event.text.unicode;
    game->pl_ui->input_pos++;
    game->pl_ui->input[game->pl_ui->input_pos] = '\0';
}

static void handle_input(game_t *game, sfEvent event)
{
    if (event.type == sfEvtTextEntered && game->pl_ui->ui_state == SAVE) {
        if (event.text.unicode == 11043) {
            game->pl_ui->input[game->pl_ui->input_pos] = '\0';
            game->pl_ui->input_pos--;
        } else {
            add_char(game, event);
        }
    }
}

void manage_events(game_t *game)
{
    sfEvent event;

    game->mouse_clicked = false;
    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(game, event);
        get_mouse_clicked(game, event);
        handle_input(game, event);
        handle_map_events(game, event);
    }
}
