/*
** EPITECH PROJECT, 2025
** my_strcmp.c
** File description:
** Comapres two strings and return different values if less, equal or more
*/

/**
 * Compares s1 string with s2 string
 * @param s1 first string to compare
 * @param s2 second string to compare
 * @return 1, 0 or -1 if s1 is respectively greater, equal, or lesser than s2
 */
int my_strcmp(char const *s1, char const *s2)
{
    if (!s1 || !s2)
        return 84;
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] > s2[i])
            return 1;
        if (s1[i] < s2[i])
            return -1;
    }
    return 0;
}
