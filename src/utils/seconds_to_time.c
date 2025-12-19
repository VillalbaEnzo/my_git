/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** seconde_to_time.c
*/

#include "../../include/my.h"

char *seconds_to_time(int seconds)
{
    char *buffer = malloc(sizeof(char) * 6);
    int minutes = seconds / 60;
    int secs = seconds % 60;

    if (!buffer)
        return NULL;
    buffer[0] = (minutes / 10) + '0';
    buffer[1] = (minutes % 10) + '0';
    buffer[2] = ':';
    buffer[3] = (secs / 10) + '0';
    buffer[4] = (secs % 10) + '0';
    buffer[5] = '\0';
    return buffer;
}
