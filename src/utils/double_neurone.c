/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** double_neurone.c
*/

#include "my.h"

float double_neurone(float x[2], float w[2])
{
    float result = 0.0;

    for (int i = 0; i < 2; i++)
        result += x[i] * w[i];
    return result;
}
