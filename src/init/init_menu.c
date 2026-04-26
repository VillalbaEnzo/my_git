/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_menu.c
*/

#include "wolf3d.h"
#include "paths.h"


static void init_texts_bnt(menu_t *menu)
{
    const char *labels[BTN_COUNT] = {"NEW GAME", "LOAD GAME", "SETTINGS",
        "QUIT"};
    sfVector2f text_pos;

    menu->font = sfFont_createFromFile(MENU_FONT);
    for (int i = 0; i < BTN_COUNT; i++) {
        menu->btn_texts[i] = sfText_create();
        sfText_setFont(menu->btn_texts[i], menu->font);
        sfText_setString(menu->btn_texts[i], labels[i]);
        sfText_setCharacterSize(menu->btn_texts[i], 40);
        sfText_setColor(menu->btn_texts[i], sfWhite);
        text_pos.x = menu->cursor_positions[i].x + 100;
        text_pos.y = menu->cursor_positions[i].y - 15;
        sfText_setPosition(menu->btn_texts[i], text_pos);
    }
}

static void init_cursor(menu_t *menu)
{
    menu->cursor_texture = sfTexture_createFromFile(CURSOR, NULL);
    menu->cursor_sprite = sfSprite_create();
    sfSprite_setScale(menu->cursor_sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setTexture(menu->cursor_sprite, menu->cursor_texture, sfTrue);
    menu->selected_btn = BTN_NEW_GAME;
    menu->cursor_positions[BTN_NEW_GAME] = (sfVector2f){460, 200};
    menu->cursor_positions[BTN_LOAD_GAME] = (sfVector2f){460, 300};
    menu->cursor_positions[BTN_SETTINGS] = (sfVector2f){460, 400};
    menu->cursor_positions[BTN_QUIT] = (sfVector2f){460, 500};
    sfSprite_setPosition(menu->cursor_sprite,
        menu->cursor_positions[menu->selected_btn]);
}

static audio_t *init_audio(char *audio_path, bool music)
{
    audio_t *audio = malloc(sizeof(audio_t));

    if (!audio)
        return NULL;
    audio->volume = 100;
    
    if (music) {
        audio->music = sfMusic_createFromFile(audio_path);
        audio->sfx = NULL;
        audio->buffer = NULL; // Initialise à NULL par sécurité
        if (!audio->music) {
            free(audio);
            return NULL;
        }
        return audio;
    }
    
    // Pour les effets sonores :
    audio->music = NULL;
    audio->sfx = sfSound_create();
    audio->buffer = sfSoundBuffer_createFromFile(audio_path); // 1. On charge le fichier dans le buffer
    
    // Vérifie que la création a bien fonctionné
    if (!audio->sfx || !audio->buffer) {
        if (audio->sfx) sfSound_destroy(audio->sfx);
        if (audio->buffer) sfSoundBuffer_destroy(audio->buffer);
        free(audio);
        return NULL;
    }
    
    sfSound_setBuffer(audio->sfx, audio->buffer); // 2. On attache le buffer au son
    return audio;
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->music = init_audio(MUSIC_MENU, true);
    if (!menu->music) {
        free(menu);
        return NULL;
    }
    menu->sfx = init_audio(SFX_BTN_MENU, false);
    if (!menu->sfx) {
        free(menu);
        return NULL;
    }
    menu->bg_texture = sfTexture_createFromFile(MENU_BG, NULL);
    menu->bg_sprite = sfSprite_create();
    sfSprite_setTexture(menu->bg_sprite, menu->bg_texture, sfTrue);
    init_cursor(menu);
    init_texts_bnt(menu);
    return menu;
}
