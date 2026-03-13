/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** display_brush_ui.c
*/

#include "my.h"

void display_brush_ui(game_t *game)
{
    sfText_setString(game->pl_ui->tb->brush->radius_text,
        game->pl_ui->tb->brush->radius_input);
    sfText_setString(game->pl_ui->tb->brush->strength_text,
        game->pl_ui->tb->brush->strength_input);
    sfRenderWindow_drawText(game->window,
        game->pl_ui->tb->brush->radius_label, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->pl_ui->tb->brush->radius_box, NULL);
    sfRenderWindow_drawText(game->window,
        game->pl_ui->tb->brush->radius_text, NULL);
    sfRenderWindow_drawText(game->window,
        game->pl_ui->tb->brush->strength_label, NULL);
    sfRenderWindow_drawRectangleShape(game->window,
        game->pl_ui->tb->brush->strength_box, NULL);
    sfRenderWindow_drawText(game->window,
        game->pl_ui->tb->brush->strength_text, NULL);
}
