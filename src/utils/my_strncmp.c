/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-7
** File description:
** my_strncmp.c
*/

#include "../include/my.h"



int my_strncmp(char const *s1, char const *s2, int n)
{
    if (my_strlen(s1) < my_strlen(s2) && n > my_strlen(s2)) {
        return -1;
    } else if (my_strlen(s1) > my_strlen(s2) && n > my_strlen(s1)) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return (s1[i] - s2[i]);
        }
    }
    return 0;
}
