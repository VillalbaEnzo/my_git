/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** neurone.c
*/

#include "my.h"

void backpropagation(float x[2], float w[2], float prediction,
    float target_y, float rate)
{
    for (int i = 0; i < 2; i++) {
        float derive = 2 * (prediction - target_y) * x[i];
        w[i] = w[i] - (rate * derive);
    }
}
