/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** enume_type_to_name.c
*/

#include "../include/my.h"

char *enum_type_to_name(type_t type)
{
    if (type == 0)
        return "ACTUATOR";
    if (type == 1)
        return "DEVICE";
    if (type == 2)
        return "PROCESSOR";
    if (type == 3)
        return "SENSOR";
    if (type == 4)
        return "WIRE";
    return NULL;
}
