/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** init_audio.c
*/

#include "wolf3d.h"

static audio_t *init_sfx(audio_t *audio, char *path)
{
    audio->music = NULL;
    audio->sfx = sfSound_create();
    audio->buffer = sfSoundBuffer_createFromFile(path);
    if (!audio->sfx || !audio->buffer) {
        if (audio->sfx)
            sfSound_destroy(audio->sfx);
        if (audio->buffer)
            sfSoundBuffer_destroy(audio->buffer);
        free(audio);
        return NULL;
    }
    sfSound_setBuffer(audio->sfx, audio->buffer);
    return audio;
}

audio_t *init_audio(char *audio_path, bool music)
{
    audio_t *audio = malloc(sizeof(audio_t));

    if (!audio)
        return NULL;
    audio->volume = 25;
    if (music) {
        audio->music = sfMusic_createFromFile(audio_path);
        audio->sfx = NULL;
        audio->buffer = NULL;
        if (!audio->music) {
            free(audio);
            return NULL;
        }
        sfMusic_setVolume(audio->music, 25);
        return audio;
    }
    return init_sfx(audio, audio_path);
}
