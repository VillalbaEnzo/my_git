/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_window.c
*/

#include "wolf3d.h"

window_t *init_window(void)
{
    window_t *win = malloc(sizeof(window_t));
    sfVideoMode mode = {1280, 720, 32};

    if (!win)
        return NULL;
    win->render = NULL;
    win->clock = NULL;
    win->render = sfRenderWindow_create(mode, "Wolfenstein 3D", sfResize |
        sfClose, NULL);
    if (!win->render)
        return NULL;
    win->clock = sfClock_create();
    if (!win->clock)
        return NULL;
    win->dt = 0.0f;
    win->is_fullscreen = false;
    sfRenderWindow_setFramerateLimit(win->render, 60);
    return win;
}
