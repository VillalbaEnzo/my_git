/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** load_btn.c
*/

#include "my.h"

bool create_load_input_box(game_t *game)
{
    game->start_menu->input_box = sfRectangleShape_create();
    if (!game->start_menu->input_box)
        return false;
    sfRectangleShape_setSize(game->start_menu->input_box,
        (sfVector2f){400, 50});
    sfRectangleShape_setPosition(game->start_menu->input_box,
        (sfVector2f){1250, 515});
    sfRectangleShape_setFillColor(game->start_menu->input_box, sfWhite);
    sfRectangleShape_setOutlineColor(game->start_menu->input_box, sfBlack);
    return true;
}

bool create_load_input_text(game_t *game)
{
    game->start_menu->load_input = sfText_create();
    if (!game->start_menu->load_input)
        return false;
    game->start_menu->input = malloc(sizeof(char) * 21);
    if (!game->start_menu->input) {
        sfText_destroy(game->start_menu->load_input);
        return false;
    }
    game->start_menu->input[0] = '\0';
    sfText_setString(game->start_menu->load_input, game->start_menu->input);
    sfText_setFont(game->start_menu->load_input, game->font);
    sfText_setCharacterSize(game->start_menu->load_input, 30);
    sfText_setColor(game->start_menu->load_input, sfBlack);
    sfText_setPosition(game->start_menu->load_input, (sfVector2f){1260, 525});
    return true;
}

static bool create_load_input_ui(game_t *game)
{
    if (!create_load_input_box(game) || !create_load_input_text(game))
        return false;
    game->start_menu->input_pos = 0;
    return true;
}

bool create_load_btn(game_t *game)
{
    sfVector2f size = {300, 70};
    sfVector2f pos = {810, 505};

    game->start_menu->load_btn->rect = sfRectangleShape_create();
    if (!game->start_menu->load_btn->rect)
        return false;
    sfRectangleShape_setSize(game->start_menu->load_btn->rect, size);
    sfRectangleShape_setPosition(game->start_menu->load_btn->rect, pos);
    game->start_menu->load_btn->texture = sfTexture_createFromFile(LOAD_BTN,
        NULL);
    if (!game->start_menu->load_btn->texture)
        return false;
    sfRectangleShape_setTexture(game->start_menu->load_btn->rect,
        game->start_menu->load_btn->texture, sfTrue);
    sfRectangleShape_setOutlineColor(game->start_menu->load_btn->rect,
        sfBlue);
    if (!create_load_input_ui(game))
        return false;
    return true;
}
