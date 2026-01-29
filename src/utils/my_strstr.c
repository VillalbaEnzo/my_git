/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strstr.c
*/

#include "../include/my.h"



char *my_strstr(char *str, char const *to_find)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if (my_strncmp(&str[i], to_find, my_strlen(to_find)) == 0) {
            return &str[i];
        }
    }
    return NULL;
}
