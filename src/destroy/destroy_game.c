/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** destroy_game.c
*/

#include "my.h"

static void destroy_brush_ui(brush_t *br)
{
    if (!br)
        return;
    if (br->radius_input)
        free(br->radius_input);
    if (br->strength_input)
        free(br->strength_input);
    if (br->radius_label)
        sfText_destroy(br->radius_label);
    if (br->radius_box)
        sfRectangleShape_destroy(br->radius_box);
    if (br->radius_text)
        sfText_destroy(br->radius_text);
    if (br->strength_label)
        sfText_destroy(br->strength_label);
    if (br->strength_box)
        sfRectangleShape_destroy(br->strength_box);
    if (br->strength_text)
        sfText_destroy(br->strength_text);
    free(br);
}

static void destroy_tools_bar(game_t *game)
{
    if (game->pl_ui->tb->raise_btn)
        sfText_destroy(game->pl_ui->tb->raise_btn);
    if (game->pl_ui->tb->lower_btn)
        sfText_destroy(game->pl_ui->tb->lower_btn);
    if (game->pl_ui->tb->flatten_btn)
        sfText_destroy(game->pl_ui->tb->flatten_btn);
    if (game->pl_ui->tb->smooth_btn)
        sfText_destroy(game->pl_ui->tb->smooth_btn);
    destroy_brush_ui(game->pl_ui->tb->brush);
    if (game->pl_ui->tb)
        free(game->pl_ui->tb);
}

static void destroy_playing(game_t *game)
{
    destroy_tools_bar(game);
    if (game->pl_ui->menu_btn)
        sfText_destroy(game->pl_ui->menu_btn);
    if (game->pl_ui->save_btn)
        sfText_destroy(game->pl_ui->save_btn);
    if (game->pl_ui->save_input)
        sfText_destroy(game->pl_ui->save_input);
    if (game->pl_ui->input_box)
        sfRectangleShape_destroy(game->pl_ui->input_box);
    if (game->pl_ui->input)
        free(game->pl_ui->input);
    if (game->pl_ui)
        free(game->pl_ui);
}

static void destroy_start_menu(game_t *game)
{
    if (game->start_menu->start_btn)
        sfRectangleShape_destroy(game->start_menu->start_btn->rect);
    if (game->start_menu->start_btn->texture)
        sfTexture_destroy(game->start_menu->start_btn->texture);
    if (game->start_menu->load_btn)
        sfRectangleShape_destroy(game->start_menu->load_btn->rect);
    if (game->start_menu->load_btn->texture)
        sfTexture_destroy(game->start_menu->load_btn->texture);
    if (game->start_menu->quit_btn)
        sfRectangleShape_destroy(game->start_menu->quit_btn->rect);
    if (game->start_menu->quit_btn->texture)
        sfTexture_destroy(game->start_menu->quit_btn->texture);
    if (game->start_menu->start_btn)
        free(game->start_menu->start_btn);
    if (game->start_menu->load_btn)
        free(game->start_menu->load_btn);
    if (game->start_menu->quit_btn)
        free(game->start_menu->quit_btn);
    if (game->start_menu)
        free(game->start_menu);
}

static void destroy_bg(game_t *game)
{
    if (game->bg->bg_sp)
        sfSprite_destroy(game->bg->bg_sp);
    if (game->bg->bg_tx)
        sfTexture_destroy(game->bg->bg_tx);
    if (game->bg)
        free(game->bg);
}

void destroy_game(game_t *game)
{
    destroy_bg(game);
    destroy_start_menu(game);
    destroy_playing(game);
    destroy_map(game);
    if (game->font)
        sfFont_destroy(game->font);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game)
        free(game);
}
