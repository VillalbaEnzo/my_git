/*
** EPITECH PROJECT, 2025
** my_strncpy.c
** File description:
** Copies n characters from a string into another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    for (int i = 0; i < n && *src != '\0'; i++) {
        *(dest + i) = *(src + i);
    }
    return (dest);
}
