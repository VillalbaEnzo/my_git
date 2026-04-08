/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** is_index.c
*/

#include "op.h"

bool is_index(int opcode)
{
    if (opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12 ||
        opcode == 14 || opcode == 15)
        return true;
    return false;
}
