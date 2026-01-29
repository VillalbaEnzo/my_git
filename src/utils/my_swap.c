/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-19
** File description:
** my_swap.c
*/

#include "../include/my.h"



void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
