/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_ui.c
*/

#include "structs.h"
#include "wolf3d.h"
#include "paths.h"

static bool init_ui_audio(ui_t *ui)
{
    ui->music = init_audio(MUSIC_MENU, true);
    if (!ui->music)
        return false;
    ui->sfx[SFX_MENU_SWITCH] = init_audio(SFX_BTN_SWITCH, false);
    ui->sfx[SFX_MENU_CLICK] = init_audio(SFX_BTN_CLICK, false);
    if (!ui->sfx[SFX_MENU_SWITCH] || !ui->sfx[SFX_MENU_CLICK]) {
        free_audio(ui->music);
        if (ui->sfx[SFX_MENU_SWITCH])
            free_audio(ui->sfx[SFX_MENU_SWITCH]);
        if (ui->sfx[SFX_MENU_CLICK])
            free_audio(ui->sfx[SFX_MENU_CLICK]);
        return false;
    }
    sfMusic_setLoop(ui->music->music, sfTrue);
    sfMusic_play(ui->music->music);
    return true;
}

ui_t *init_ui(void)
{
    ui_t *ui = malloc(sizeof(ui_t));

    if (!ui)
        return NULL;
    ui->menu = init_menu();
    if (!ui->menu) {
        free(ui);
        return NULL;
    }
    ui->music = NULL;
    for (int i = 0; i < SFX_MENU_COUNT; i++)
        ui->sfx[i] = NULL;
    if (!init_ui_audio(ui)) {
        free(ui);
        return NULL;
    }
    ui->settings = init_setting();
    return ui;
}
