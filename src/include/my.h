/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include "shell.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdarg.h>
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483648)

typedef enum type_e {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE
} type_t;

typedef struct node_s {
    type_t type;
    char *name;
    int id;
    struct node_s *next;
} node_t;

typedef struct context_s {
    node_t *head;
    int next_id;
} context_t;

int my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int mini_printf(const char *format, ...);
char *my_strdup(char const *src);
int my_getnbr(char const *str);
int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *enum_type_to_name(type_t type);

#endif
