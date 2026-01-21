/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strncmp.c
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;
    int car = 0;

    for (i = 0; i < n; i++)
        if (s1[i] != s2[i] ||
            s1[i] == '\0' ||
            s2[i] == '\0') {
            car = (char)s1[i] - (char)s2[i];
            return car;
        }
    return 0;
}
