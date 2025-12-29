/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include "struct.h"
    #include "stdlib.h"
    #include <stdarg.h>
    #include <unistd.h>
    #define LOADAVG_PATH "/proc/loadavg"
    #define UPTIME_PATH "/proc/uptime"
    #define STAT_PATH "/proc/stat"
    #define MEMINFO_PATH "/proc/meminfo"
    #define PROC_PATH "/proc"

/*LIB*/
int my_ls(int ac, char **av, char **cwd);
void my_putchar(char c);
int my_putchar_int(char c);
int my_putstr(char const *str);
int my_put_nbr(long nb);
int mini_printf(char const *format, ...);
int my_printf(char const *format, ...);
int my_compute_factorial_rec(int nb);
void my_putchar(char c);
int my_isneg(int n);
void my_swap(int *a, int *b);
int my_putstr(const char *str);
int my_strlen(const char *str);
int my_getnbr(const char *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, char *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char *to_find);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(const char *str);
int my_str_isnum(const char *str);
int my_str_islower(const char *str);
int my_str_isupper(const char *str);
int my_str_isprintable(const char *str);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, int nb);
char *my_itoa(int nb, char *str);
char **my_str_to_word_array(char const *str);
int my_print_unsigned(long nb);
int my_putchar_int(char c);
int my_putchar_int_maj(char c);
int my_putstr_maj(char const *str);
int my_adresse(unsigned long nb);
int my_hexadecimal(unsigned long nb);
int my_octal(int nb);
int my_strstrlen(char **str);
char **open_read(char *path);
int my_perror(char const *str);
char *my_strdup(char const *str);
float my_getfloatnbr(char const *str);

/*PROJECT FUNCTIONS*/
void free_top(top_t *t);
void print_helper(void);
p_t *init_p(void);
inf_t *init_inf(void);
process_t *init_process(void);
set_t *init_set(void);
system_t *init_system(void);
top_t *define_top(void);
int parsing_av(char **av, top_t *t);
void print_top(top_t *top);

#endif /*MY_H*/
