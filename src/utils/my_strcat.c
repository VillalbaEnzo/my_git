/*
** EPITECH PROJECT, 2025
** my_strcat.c
** File description:
** Concatenates two strings
*/

static int my_strlen(char const *str)
{
    int cnt = 0;

    while (*str != '\0') {
        str++;
        cnt++;
    }
    return cnt;
}

char *my_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int cnt = 0;

    if (!dest || !src)
        return dest;
    while (*src != '\0') {
        *(dest + len_dest + cnt) = *src;
        cnt++;
        src++;
    }
    *(dest + len_dest + cnt) = '\0';
    return dest;
}
