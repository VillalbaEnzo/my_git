/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_settings.c
*/

#include "wolf3d.h"
#include "paths.h"

static void init_setting_btn(settings_t *set)
{
    const char *labels[] = {"MUSIC", "SFX", "RESOLUTION: 1280x720", "BACK"};
    sfVector2f text_pos;

    set->font = sfFont_createFromFile(MENU_FONT);
    for (int i = 0; i < SET_COUNT; i++) {
        set->btn_texts[i] = sfText_create();
        sfText_setFont(set->btn_texts[i], set->font);
        sfText_setString(set->btn_texts[i], labels[i]);
        sfText_setCharacterSize(set->btn_texts[i], 35);
        sfText_setColor(set->btn_texts[i], sfWhite);
        text_pos.x = set->cursor_positions[i].x + 100;
        text_pos.y = set->cursor_positions[i].y - 15;
        sfText_setPosition(set->btn_texts[i], text_pos);
    }
}

static void init_slider(settings_t *set, int i, float volume, float y)
{
    set->slider_bg[i] = sfRectangleShape_create();
    sfRectangleShape_setSize(set->slider_bg[i], (sfVector2f){300, 30});
    sfRectangleShape_setFillColor(set->slider_bg[i], (sfColor){50, 50, 50,
            255});
    sfRectangleShape_setPosition(set->slider_bg[i], (sfVector2f){600, y});
    set->slider_fill[i] = sfRectangleShape_create();
    sfRectangleShape_setSize(set->slider_fill[i],
        (sfVector2f){(volume / 100.0) * 300, 30});
    sfRectangleShape_setFillColor(set->slider_fill[i], sfWhite);
    sfRectangleShape_setPosition(set->slider_fill[i], (sfVector2f){600, y});
}

static void init_cursor(settings_t *set)
{
    set->cursor_texture = sfTexture_createFromFile(CURSOR, NULL);
    set->cursor_sprite = sfSprite_create();
    sfSprite_setScale(set->cursor_sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setTexture(set->cursor_sprite, set->cursor_texture, sfTrue);
    set->selected_btn = BTN_NEW_GAME;
    set->cursor_positions[SET_MUSIC] = (sfVector2f){350, 200};
    set->cursor_positions[SET_SFX] = (sfVector2f){350, 300};
    set->cursor_positions[SET_RESIZE] = (sfVector2f){350, 400};
    set->cursor_positions[SET_BACK] = (sfVector2f){350, 500};
    sfSprite_setPosition(set->cursor_sprite,
        set->cursor_positions[set->selected_btn]);
}

settings_t *init_setting(void)
{
    settings_t *set = malloc(sizeof(settings_t));

    if (!set)
        return NULL;
    set->bg_sprite = sfSprite_create();
    set->bg_texture = sfTexture_createFromFile(SETTING_BG, NULL);
    sfSprite_setTexture(set->bg_sprite, set->bg_texture, sfTrue);
    set->selected_btn = SET_MUSIC;
    init_cursor(set);
    init_slider(set, 0, 100.0, set->cursor_positions[SET_MUSIC].y);
    init_slider(set, 1, 100.0, set->cursor_positions[SET_SFX].y);
    init_setting_btn(set);
    return set;
}
