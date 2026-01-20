/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strlowcase.c
*/

int my_strlen_lowercase(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *my_strlowcase(char *str)
{
    int len = my_strlen_lowercase(str);
    int i = 0;

    for (; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return str;
}
