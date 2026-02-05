/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** hash.c
*/

#include "hashtable.h"

int hash(char *key, int len)
{
    unsigned int hash = MAGIC_NUMBER;

    if (!key || len <= 0)
        return 0;
    for (int i = 0; key[i]; i++) {
        hash = (hash * 33) ^ (unsigned char)key[i];
        hash ^= (hash << 13);
        hash ^= (hash >> 17);
        hash ^= (hash << 5);
    }
    return (int)(hash & 0b1111111111111111111111111111111);
}
