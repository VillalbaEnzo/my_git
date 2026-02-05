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

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>

char *my_strdup(char const *src);
int my_show_word_array(char *const *tab);
void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
void my_swap_str(char **a, char **b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int mini_printf(const char *format, ...);
void my_bubble_sort(int *arr, int n);
int my_put_nbr_u(unsigned int nb, int nb_char);

#endif
