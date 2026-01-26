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
    unsigned int hm = HASH_MIXER;

    (void)len;
    if (!key)
        return 0;
    for (int i = 0; key[i]; i++)
        hash = (hash * 33) + key[i];
    return (int)(hash * hm);
}
