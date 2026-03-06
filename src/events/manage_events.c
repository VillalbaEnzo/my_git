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

static void handle_backspace(game_t *game)
{
    ui_state_t st = game->pl_ui->ui_state;
    brush_t *br = game->pl_ui->tb->brush;

    if (st == SAVE && game->pl_ui->input_pos > 0) {
        game->pl_ui->input_pos--;
        game->pl_ui->input[game->pl_ui->input_pos] = '\0';
    }
    if (st == INPUT_RADIUS && br->radius_pos > 0) {
        br->radius_pos--;
        br->radius_input[br->radius_pos] = '\0';
    }
    if (st == INPUT_STRENGTH && br->strength_pos > 0) {
        br->strength_pos--;
        br->strength_input[br->strength_pos] = '\0';
    }
}

static void handle_typing(game_t *game, sfEvent event)
{
    ui_state_t st = game->pl_ui->ui_state;
    brush_t *br = game->pl_ui->tb->brush;

    if (st == SAVE && game->pl_ui->input_pos < 20) {
        game->pl_ui->input[game->pl_ui->input_pos] = event.text.unicode;
        game->pl_ui->input_pos++;
        game->pl_ui->input[game->pl_ui->input_pos] = '\0';
    }
    if (st == INPUT_RADIUS && br->radius_pos < 10 &&
        event.text.unicode >= '0' && event.text.unicode <= '9') {
        br->radius_input[br->radius_pos] = event.text.unicode;
        br->radius_pos++;
        br->radius_input[br->radius_pos] = '\0';
    }
    if (st == INPUT_STRENGTH && br->strength_pos < 10 &&
        event.text.unicode >= '0' && event.text.unicode <= '9') {
        br->strength_input[br->strength_pos] = event.text.unicode;
        br->strength_pos++;
        br->strength_input[br->strength_pos] = '\0';
    }
}

static void handle_save_load(game_t *game)
{
    if (game->state == PLAYING && game->pl_ui->ui_state == SAVE) {
        save_map_to_file(game);
        game->pl_ui->ui_state = MENU;
    }
    game->pl_ui->input[0] = '\0';
    game->pl_ui->input_pos = 0;
}

static void handle_load_load(game_t *game)
{
    if (game->state == LOADMAP) {
        load_map_from_file(game);
        game->state = PLAYING;
    }
    game->start_menu->input[0] = '\0';
    game->start_menu->input_pos = 0;
}

static void handle_input(game_t *game, sfEvent event)
{
    ui_state_t st = game->pl_ui->ui_state;

    if (event.type != sfEvtTextEntered)
        return;
    if (event.text.unicode == '\r' || event.text.unicode == '\n') {
        if (st == INPUT_RADIUS || st == INPUT_STRENGTH)
            game->pl_ui->ui_state = RAISE;
        if (st == SAVE)
            handle_save_load(game);
        if (game->state == LOADMAP)
            handle_load_load(game);
        return;
    }
    if (event.text.unicode == 8 || event.text.unicode == '\b') {
        handle_backspace(game);
        return;
    }
    handle_typing(game, event);
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
