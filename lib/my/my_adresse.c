/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-21
** File description:
** my_adresse.c
*/

#include "../includes/my.h"

static int my_size_hexadecimal(unsigned long nb)
{
    int size = 0;

    while (nb > 0) {
        nb /= 16;
        size++;
    }
    return size;
}

int my_hexadecimal(unsigned long nb)
{
    char *buffer;
    int i = 0;
    int out;

    if (nb == 0)
        return my_putstr("0");
    buffer = malloc(my_size_hexadecimal(nb) + 1);
    if (buffer == NULL)
        return -1;
    while (nb > 0) {
        buffer[i] = "0123456789abcdef"[nb % 16];
        nb /= 16;
        i++;
    }
    buffer[i] = '\0';
    out = my_putstr(my_revstr(buffer));
    free(buffer);
    return out;
}

int my_adresse(unsigned long nb)
{
    my_putstr("0x");
    my_hexadecimal(nb);
    return 0;
}

int my_octal(int nb)
{
    char *bufer;
    char const *base = "0123456789";
    int r = 0;
    int i = 0;

    bufer = malloc(sizeof(char *) * (my_size_hexadecimal(nb)) + 1);
    if (nb == 0)
        return my_put_nbr(0);
    while (nb > 0) {
        r = nb % 8;
        bufer[i] = base[r];
        nb /= 8;
        i++;
    }
    bufer[i] = '\0';
    return my_putstr(my_revstr(bufer));
}
