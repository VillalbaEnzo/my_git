/*
** EPITECH PROJECT, 2025
** Stumper
** File description:
** calculator.c
*/

#include "my.h"


int calculate_one_grade(char c, int credit)
{
    if (c == 'A')
        return credit * 4;
    if (c == 'B')
        return credit * 3;
    if (c == 'C')
        return credit * 2;
    if (c == 'D')
        return credit * 1;
    return 0;
}
