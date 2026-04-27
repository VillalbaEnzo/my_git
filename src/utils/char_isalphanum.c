/*
** EPITECH PROJECT, 2026
** 42sh [WSL: Ubuntu]
** File description:
** char_isalphanum
*/

#include "mysh.h"

bool c_is_alphanum(char c)
{
    return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') ||
        ('0' <= c && c <= '9'));
}
