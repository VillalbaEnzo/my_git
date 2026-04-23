/*
** EPITECH PROJECT, 2025
** next
** File description:
** main.c
*/

#include "my.h"

void handle_prog(char *str, int n)
{
    int neg = 0;

    for (int i = 0; str[i]; i++) {
        if (!is_alpha(str[i]))
            continue;
        if (n < 0) {
            n = n * -1;
            neg = 1;
        }
        if (n > 26)
            n = n % 26;
        if (neg) {
            neg = 0;
            n = n * -1;
        }
        if (is_min(str[i]))
            str[i] = handle_min(str[i], n);
        if (is_maj(str[i]))
            str[i] = handle_maj(str[i], n);
    }
}
