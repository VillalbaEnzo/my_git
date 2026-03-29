/*
** EPITECH PROJECT, 2025
** my_strncmp.c
** File description:
** Compares n first bytes of two given functions
*/
#include <stdlib.h>

/**
 * Compare n bytes of s1 with s2
 * @param s1 first string to compare
 * @param s2 second string to compare
 * @param n number of bytes to compare
 * @return 1, 0 or -1 if s1 is superior, equal, or inferior to s2
 */
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
