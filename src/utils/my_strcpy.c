/*
** EPITECH PROJECT, 2025
** my_strcpy.c
** File description:
** Copies a string into another
*/

/**
 * Copies src into dest
 * @param dest Allocated string to copy char into
 * @param src Source string
 * @return pointer to dest string
*/
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
