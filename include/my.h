/*
** EPITECH PROJECT, 2025
** A-maze-d
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <ctype.h>
    #define SAVE_FILE "crypt"
    #define INT_MAX 2147483647
    #define INT_MIN -2147483648

/* UTILS */

int my_getnbr(char const *str);
int is_num_from_str(char *str);
int ist_num(char c);
char *read_file(const char *filename);
int is_alpha(char c);
int is_maj(char c);
int is_min(char c);
int write_file(char *str);

/* HANDLE */

void handle_prog(char *str, int n);
char handle_maj(char c, int n);
char handle_min(char c, int n);

#endif
