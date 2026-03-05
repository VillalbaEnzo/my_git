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

static void add_number_to_input(char *input, int *pos, sfEvent event)
{
    if (*pos == 10)
        return;
    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
        input[*pos] = event.text.unicode;
        (*pos)++;
        input[*pos] = '\0';
    }
}

static void handle_input(game_t *game, sfEvent event)
{
    if (event.type != sfEvtTextEntered)
        return;

    // Gestion du retour en arrière (code 8 ou '\b' selon l'OS)
    if (event.text.unicode == 8 || event.text.unicode == '\b') {
        if (game->pl_ui->ui_state == SAVE && game->pl_ui->input_pos > 0) {
            game->pl_ui->input_pos--;
            game->pl_ui->input[game->pl_ui->input_pos] = '\0';
        } else if (game->pl_ui->ui_state == INPUT_RADIUS && game->pl_ui->tb->brush->radius_pos > 0) {
            game->pl_ui->tb->brush->radius_pos--;
            game->pl_ui->tb->brush->radius_input[game->pl_ui->tb->brush->radius_pos] = '\0';
        } else if (game->pl_ui->ui_state == INPUT_STRENGTH && game->pl_ui->tb->brush->strength_pos > 0) {
            game->pl_ui->tb->brush->strength_pos--;
            game->pl_ui->tb->brush->strength_input[game->pl_ui->tb->brush->strength_pos] = '\0';
        }
        return;
    }

    // Ajout de caractères classiques
    if (game->pl_ui->ui_state == SAVE) {
        add_char(game, event);
    } else if (game->pl_ui->ui_state == INPUT_RADIUS) {
        add_number_to_input(game->pl_ui->tb->brush->radius_input, &game->pl_ui->tb->brush->radius_pos, event);
    } else if (game->pl_ui->ui_state == INPUT_STRENGTH) {
        add_number_to_input(game->pl_ui->tb->brush->strength_input, &game->pl_ui->tb->brush->strength_pos, event);
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
