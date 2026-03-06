/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** create_brush_ui.c
*/

#include "my.h"

static void create_radius_text_label(game_t *game)
{
    game->pl_ui->tb->brush->radius_label = sfText_create();
    sfText_setString(game->pl_ui->tb->brush->radius_label, "Radius");
    sfText_setFont(game->pl_ui->tb->brush->radius_label, game->font);
    sfText_setCharacterSize(game->pl_ui->tb->brush->radius_label, 25);
    sfText_setPosition(game->pl_ui->tb->brush->radius_label,
        (sfVector2f){1725, 600});
}

static void create_radius_box(game_t *game)
{
    game->pl_ui->tb->brush->radius_box = sfRectangleShape_create();
    sfRectangleShape_setFillColor(game->pl_ui->tb->brush->radius_box,
        sfWhite);
    sfRectangleShape_setOutlineColor(game->pl_ui->tb->brush->radius_box,
        sfBlack);
    sfRectangleShape_setSize(game->pl_ui->tb->brush->radius_box,
        (sfVector2f){150, 30});
    sfRectangleShape_setPosition(game->pl_ui->tb->brush->radius_box,
        (sfVector2f){1725, 630});
}

static void create_radius_text(game_t *game)
{
    game->pl_ui->tb->brush->radius_text = sfText_create();
    sfText_setFont(game->pl_ui->tb->brush->radius_text, game->font);
    sfText_setCharacterSize(game->pl_ui->tb->brush->radius_text, 25);
    sfText_setColor(game->pl_ui->tb->brush->radius_text, sfBlack);
    sfText_setPosition(game->pl_ui->tb->brush->radius_text,
        (sfVector2f){1730, 630});
}

static void create_strength_text_label(game_t *game)
{
    game->pl_ui->tb->brush->strength_label = sfText_create();
    sfText_setString(game->pl_ui->tb->brush->strength_label, "Strength");
    sfText_setFont(game->pl_ui->tb->brush->strength_label, game->font);
    sfText_setCharacterSize(game->pl_ui->tb->brush->strength_label, 25);
    sfText_setPosition(game->pl_ui->tb->brush->strength_label,
        (sfVector2f){1725, 680});
}

static void create_strength_box(game_t *game)
{
    game->pl_ui->tb->brush->strength_box = sfRectangleShape_create();
    sfRectangleShape_setFillColor(game->pl_ui->tb->brush->strength_box,
        sfWhite);
    sfRectangleShape_setOutlineColor(game->pl_ui->tb->brush->strength_box,
        sfBlack);
    sfRectangleShape_setSize(game->pl_ui->tb->brush->strength_box,
        (sfVector2f){150, 30});
    sfRectangleShape_setPosition(game->pl_ui->tb->brush->strength_box,
        (sfVector2f){1725, 710});
}

static void create_strength_text(game_t *game)
{
    game->pl_ui->tb->brush->strength_text = sfText_create();
    sfText_setFont(game->pl_ui->tb->brush->strength_text, game->font);
    sfText_setCharacterSize(game->pl_ui->tb->brush->strength_text, 25);
    sfText_setColor(game->pl_ui->tb->brush->strength_text, sfBlack);
    sfText_setPosition(game->pl_ui->tb->brush->strength_text,
        (sfVector2f){1730, 710});
}

bool create_brush_ui(game_t *game)
{
    game->pl_ui->tb->brush->radius_input = malloc(sizeof(char) * 11);
    if (!game->pl_ui->tb->brush->radius_input)
        return false;
    game->pl_ui->tb->brush->strength_input = malloc(sizeof(char) * 11);
    if (!game->pl_ui->tb->brush->strength_input) {
        free(game->pl_ui->tb->brush->radius_input);
        return false;
    }
    game->pl_ui->tb->brush->radius_input[0] = '\0';
    game->pl_ui->tb->brush->strength_input[0] = '\0';
    game->pl_ui->tb->brush->radius_pos = 0;
    game->pl_ui->tb->brush->strength_pos = 0;
    create_radius_text_label(game);
    create_radius_box(game);
    create_radius_text(game);
    create_strength_text_label(game);
    create_strength_box(game);
    create_strength_text(game);
    return true;
}
