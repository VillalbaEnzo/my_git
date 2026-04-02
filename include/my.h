/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday07-8
** File description:
** my.h
*/

#ifndef INCLUDE
    #define INCLUDE
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483648)

    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>

typedef enum grade_e {
    E,
    D,
    C,
    B,
    A
} grade_t;

int my_strlen(const char *str);
int is_num(char *str);
int calculate_one_grade(char c, int credit);

#endif
