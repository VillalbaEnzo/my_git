/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-5 [WSL: Ubuntu-24.04]
** File description:
** free_audio.c
*/

#include "wolf3d.h"
#include "structs.h"

void free_audio(audio_t *audio)
{
    if (!audio)
        return;
    if (audio->music)
        sfMusic_destroy(audio->music);
    if (audio->sfx)
        sfSound_destroy(audio->sfx);
    if (audio->buffer)
        sfSoundBuffer_destroy(audio->buffer);
    free(audio);
}
