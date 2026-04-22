/*
** EPITECH PROJECT, 2025
** my_strcmp.c
** File description:
** Comapres two strings and return different values if less, equal or more
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

static int get_len(char const *s1, char const *s2)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    if (len1 >= len2)
        return len1;
    return len2;
}

int my_strcmp(char const *s1, char const *s2)
{
    int lendef = 0;

    if (!s1 || !s2)
        return 84;
    lendef = get_len(s1, s2);
    for (int i = 0; i < lendef; i++) {
        if (*(s1 + i) > *(s2 + i)) {
            return 1;
        }
        if (*(s1 + i) < *(s2 + i)) {
            return -1;
        }
    }
    return 0;
}
