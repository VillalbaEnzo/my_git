/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18 [WSL: Ubuntu-24.04]
** File description:
** float_special
*/

#include "../include/my.h"

static const char *get_special_str(double value, int uppercase, int sign_char)
{
    if (value != value) {
        if (sign_char == '+')
            return uppercase ? "+NAN" : "+nan";
        return uppercase ? "NAN" : "nan";
    }
    if (value == 1.0 / 0.0) {
        if (sign_char == '+')
            return uppercase ? "+INF" : "+inf";
        if (sign_char == ' ')
            return uppercase ? " INF" : " inf";
        return uppercase ? "INF" : "inf";
    }
    if (value == -1.0 / 0.0)
        return uppercase ? "-INF" : "-inf";
    return NULL;
}

int print_special_float_value(double value, int uppercase, int *count)
{
    if (value != value) {
        *count += uppercase ? my_putstr("NAN") : my_putstr("nan");
        return 1;
    }
    if (value == 1.0 / 0.0) {
        *count += uppercase ? my_putstr("INF") : my_putstr("inf");
        return 1;
    }
    if (value == -1.0 / 0.0) {
        *count += uppercase ? my_putstr("-INF") : my_putstr("-inf");
        return 1;
    }
    return 0;
}

int get_special_float_str_len(const char *str)
{
    int len = 0;

    while (str[len])
        len++;
    return len;
}
