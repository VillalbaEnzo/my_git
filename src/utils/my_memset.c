/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** my_memset
*/
#include "op.h"

/**
 * Set n bytes of to_set to c
 * @param to_set memory location to set
 * @param c value bytes will be set at
 * @param n number of bytes to be set
 * @return void pointer to set memory
*/
void *my_memset(void *to_set, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ((unsigned char *)to_set)[i] = c;
    return to_set;
}
