/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday06-25
** File description:
**  my_strcapitalize.c
*/

#include "../includes/my.h"
#include "unistd.h"

void apply_case(int capitalize_next, char *c)
{
    if (capitalize_next && *c >= 'a' && *c <= 'z') {
        *c -= 32;
    } else if (!capitalize_next && *c >= 'A' && *c <= 'Z') {
        *c += 32;
    }
}

void capitalise(int i, int *capitalize_next, char *str)
{
    if ((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= '0' && str[i] <= '9')) {
        apply_case(*capitalize_next, &str[i]);
        *capitalize_next = 0;
    } else {
        *capitalize_next = 1;
    }
}

char *my_strcapitalize(char *str)
{
    int i = 0;
    int capitalize_next = 1;

    if (str == NULL)
        return NULL;
    for (i = 0; str[i] != '\0'; i++) {
        capitalise(i, &capitalize_next, str);
    }
    return str;
}
