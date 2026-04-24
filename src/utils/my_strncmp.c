/*
** EPITECH PROJECT, 2025
** my_strncmp.c
** File description:
** Compares n first bytes of two given functions
*/
#include "utils.h"
#include <stdlib.h>

int my_strncmp(char const *s1, char const *s2, int n)
{
    if (s1 == NULL || s2 == NULL)
        return 2;
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0' && i < n; i++) {
        if (s1[i] > s2[i])
            return 1;
        if (s1[i] < s2[i])
            return -1;
    }
    return 0;
}
