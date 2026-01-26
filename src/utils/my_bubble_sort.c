/*
** EPITECH PROJECT, 2025
** Stumper
** File description:
** my_bubble_sort.c
*/

#include "../include/my.h"

static void if_func(int *arr, int j, int *swapped)
{
    if (arr[j] > arr[j + 1]) {
        my_swap(&arr[j], &arr[j + 1]);
        *swapped = 1;
    }
}

void my_bubble_sort(int *arr, int n)
{
    int i = 0;
    int j = 0;
    int swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++)
            if_func(arr, j, &swapped);
        if (swapped == 0)
            break;
    }
}
