/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_str_isalpha.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_str_isalpha(char const *str)
{
    if (str == NULL)
        return 84;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z')
                || (str[i] >= 'a' && str[i] <= 'z'))) {
            return 0;
        }
    }
    return 1;
}
