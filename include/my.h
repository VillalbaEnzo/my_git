/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <wchar.h>
    #include "my_printf.h"

    #ifndef INT_MAX
        #define INT_MAX 2147483647
    #endif

    #ifndef INT_MIN
        #define INT_MIN (-2147483648)
    #endif


int my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_printf(const char *format, ...);
int my_getnbr(const char *str);
int is_digit(char c);
int check_maxint(int signe, int nb, int digit);
int my_strlen(char const *str);
int my_putnstr(const char *str, int n);
void my_putwchar(wint_t wc, int *count);
void my_putnwstr(const wchar_t *wstr, int n, int *count);
int my_wstrlen(const wchar_t *wstr);
int wchar_n_bytes(wint_t wc);
void put_wchar_4bytes(wint_t wc, int *count);
void put_wchar_3bytes(wint_t wc, int *count);
void put_wchar_2bytes(wint_t wc, int *count);
void put_wchar_1byte(wint_t wc, int *count);
int my_put_nbr_octal(unsigned long long nb);
int my_put_float(double value, int precision);
double my_power(double base, int exp);
double my_abs_double(double value);
void print_padding(char c, int n, int *count);
int print_special_float_value(double value, int uppercase, int *count);
int get_special_float_str_len(const char *str);
int get_sign_char_int(long long value, format_spec_t *spec);
int get_sign_char_float(double value, format_spec_t *spec);
void print_number_signed(long long nb, int *count);
void print_number_unsigned(unsigned long long value, int *count);
int count_digits_signed(long long nb);
int count_digits_unsigned(unsigned long long nb);
int my_put_hexa(unsigned long long number, format_spec_t *spec);

typedef struct int_print_params_s {
    int num_len;
    int prec_pad;
    int sign_char;
    int width_pad;
} int_print_params_t;

typedef struct unsigned_print_params_s {
    int num_len;
    int prec_pad;
    int width_pad;
} unsigned_print_params_t;

typedef struct str_print_params_s {
    int str_len;
    int prec_pad;
    int sign_char;
    int width_pad;
} str_print_params_t;

typedef struct {
    wchar_t *wstr;
    int chars_to_print;
    int padding;
    int flags;
} wstr_print_info_t;

typedef struct hexa_flags_s {
    int has_prefix;
    int is_upper;
} hexa_flags_t;

typedef struct pointer_flags_s {
    int has_prefix;
} pointer_flags_t;

typedef struct sci_print_params_s {
    double value;
    int precision;
    int exponent;
    int uppercase;
} sci_print_params_t;

typedef struct sci_format_ctx_s {
    int sign_char;
    int width_pad;
} sci_format_ctx_t;

int handle_conversion(format_spec_t *spec, va_list args);
int handle_int(format_spec_t *spec, va_list args);
int handle_unsigned(format_spec_t *spec, va_list args);
int handle_char(format_spec_t *spec, va_list args);
int handle_str(format_spec_t *spec, va_list args);
int handle_octal(format_spec_t *spec, va_list args);
int handle_float(format_spec_t *spec, va_list args);
int handle_scientific(format_spec_t *spec, va_list args);
int handle_float_auto(format_spec_t *spec, va_list args);
int handle_hexa(format_spec_t *spec, va_list args);
int handle_pointer(format_spec_t *spec, va_list args);
int handle_n(format_spec_t *spec, va_list args);
int handle_hexa_float(format_spec_t *spec, va_list args);

#endif
