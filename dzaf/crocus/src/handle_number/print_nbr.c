/*
** EPITECH PROJECT, 2025
** crocus
** File description:
** print_nbr.c
*/

#include "my.h"

static void print_space(char *nbr, int j)
{
    if (nbr[j + 1])
        write(1, " ", 1);
}

static void put_letter(const char *line, char letter)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == '0')
            write(1, &letter, 1);
        if (line[i] == ' ')
            write(1, " ", 1);
        if (line[i] != ' ' && line[i] != '0')
            write(1, &line[i], 1);
    }
}

void print_nbr(char *nbr, char *letter)
{
    int index = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; nbr[j]; j++) {
            index = nbr[j] - '0';
            put_letter(number[index].line[i], letter[j]);
            print_space(nbr, j);
        }
        write(1, "\n", 1);
    }
}
