/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday04-48
** File description:
**  my_sort_int_array.c
*/

#include "../includes/my.h"
#include <unistd.h>

void loop(int *array, int size, int *validator)
{
    int temp = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] < array[i - 1]) {
            temp = array[i];
            array[i] = array[i - 1];
            array[i - 1] = temp;
            *validator = 0;
        }
    }
}

void my_sort_int_array(int *array, int size)
{
    int validator = 0;

    while (validator != 1) {
        validator = 1;
        loop(array, size, &validator);
    }
}
