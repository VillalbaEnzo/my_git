/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-8
** File description:
** my_show_word_array.c
*/

#include "../include/my.h"



int my_show_word_array(char *const *tab)
{
    if (tab[0] == NULL)
        return 1;
    for (int i = 0; tab[i] != 0; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return 0;
}
