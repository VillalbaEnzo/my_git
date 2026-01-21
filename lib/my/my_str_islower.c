/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
** my_strislower.c
*/

#include "../includes/my.h"
#include "unistd.h"

int my_str_islower(char const *str)
{
    if (str == NULL)
        return 84;
    if (!str[0])
        return 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 'a' || str[i] > 'z') {
            return 0;
        }
    }
    return 1;
}
