/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-26
** File description:
** my_sqrt.c
*/

#include "my.h"

float my_sqrt(float number)
{
    float x = number;
    float y = 1;
    float e = 0.000001;

    while (x - y > e) {
        x = (x + y) / 2;
        y = number / x;
    }
    return x;
}
