/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <stdlib.h>

void my_putchar(char c, int fd);
int my_putstr(char const *str, int fd);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char *src);
char *my_strncpy(char *dest, char const *src, int n);
int count_args(char **arg_array, int last_pos);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strcat(char *dest, char const *src);
int my_put_nbr(long nbr, int *cnt, int fd);
int mini_printf(int fd, const char *format, ...);
int is_operator(char *token);
int is_symbol(char *token);
void *my_calloc(size_t nmemb, size_t size);
void *my_memset(void *to_set, int c, size_t n);

#endif /* !UTILS_H_ */
