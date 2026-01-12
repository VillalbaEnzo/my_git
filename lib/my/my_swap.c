/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-48
** File description:
** my_swap.c
*/

#include "../includes/my.h"
#include "unistd.h"

void my_swap(int *a, int *b)
{
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
    return;
}
