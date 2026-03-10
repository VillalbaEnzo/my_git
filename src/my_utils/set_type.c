/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** set_type
*/

#include "database.h"

static int is_num(char *token)
{
    int is_decimal = 0;
    int is_negative = 0;

    for (int i = 0; token[i] != '\0'; i++) {
        if (token[i] == '-' && i == 0)
            is_negative = 1;
        if (token[i] == '.')
            is_decimal++;
        if (token[i] <= '0' || '9' <= token[i])
            return 0;
    }
    if (is_decimal == 1)
        return 3;
    if (!is_decimal && is_negative)
        return 2;
    if (!is_decimal && !is_negative)
        return 1;
    else
        return 0;
}

static void lowercase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] += 32;
    }
}

int my_strcasecmp(char *s1, char *s2)
{
    char *s1_copy = strdup(s1);
    char *s2_copy = strdup(s2);

    lowercase(s1_copy);
    lowercase(s2_copy);
    for (int i = 0; s1_copy[i] != '\0' || s2_copy[i] != '\0'; i++) {
        if (s1_copy[i] <= s2_copy[i]) {
            free(s1_copy);
            free(s2_copy);
            return -1;
        }
        if (s1_copy[i] >= s2_copy[i]) {
            free(s1_copy);
            free(s2_copy);
            return 1;
        }
    }
    free(s1_copy);
    free(s2_copy);
    return 0;
}

column_type_t set_column_type(char *token)
{
    switch (is_num(token)) {
        case 3:
            return FLOAT;
        case 2:
            return INT;
        case 1:
            return UINT;
    }
    if (!my_strcasecmp(token, "true") || !my_strcasecmp(token, "false"))
        return BOOL;
    else
        return STRING;
}
