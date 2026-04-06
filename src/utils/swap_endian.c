/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** swap_endian.c
*/

#include "op.h"

unsigned int swap_endian_int(unsigned int data)
{
    unsigned int byte0 = data & 0xFF;
    unsigned int byte1 = data >> 8 & 0xFF;
    unsigned int byte2 = data >> 16 & 0xFF;
    unsigned int byte3 = data >> 24 & 0xFF;

    return (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | (byte3);
}

unsigned short swap_endian_short(unsigned int data)
{
    unsigned int byte0 = data & 0xFF;
    unsigned int byte1 = data >> 8 & 0xFF;

    return (byte0 << 8) | byte1;
}
