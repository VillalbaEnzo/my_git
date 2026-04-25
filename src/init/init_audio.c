/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_audio.c
*/

#include "structs.h"
#include "wolf3d.h"

audio_t *init_audio(void)
{
    audio_t *audio = malloc(sizeof(audio_t));

    if (!audio)
        return NULL;
    audio->bg_music = sfMusic_createFromFile(BG_MUSIC_PATH);
    if (!audio->bg_music) {
        free(audio);
        return NULL;
    }
    audio->volume = 100;
    sfMusic_setLoop(audio->bg_music, sfTrue);
    return audio;
}
