/*
** EPITECH PROJECT, 2025
** G-CPE-101-LYN-1-1-myprintf-18
** File description:
** str.c
*/

#include "../include/my.h"

static void adjust_precision(format_spec_t *spec, int *str_len,
    int *prec_pad, char *value)
{
    if (spec->has_precision && spec->precision < *str_len)
        *str_len = spec->precision;
}

static void print_str_with_padding(format_spec_t *spec, char *value,
    int *count, str_print_params_t *params)
{
    if (!(spec->flags & FLAG_MINUS)) {
        print_padding(' ', params->width_pad, count);
        *count += my_putnstr(value, params->str_len);
    }
    if (spec->flags & FLAG_MINUS) {
        *count += my_putnstr(value, params->str_len);
        print_padding(' ', params->width_pad, count);
    }
}

static void print_wstr_with_padding(wstr_print_info_t *info, int *count)
{
    if (!(info->flags & FLAG_MINUS))
        print_padding(' ', info->padding, count);
    my_putnwstr(info->wstr, info->chars_to_print, count);
    if (info->flags & FLAG_MINUS)
        print_padding(' ', info->padding, count);
}

static void handle_normal_str(format_spec_t *spec, va_list args,
    int *count)
{
    char *str = va_arg(args, char *);
    int total_len = 0;
    str_print_params_t params;
    int is_null = (str == NULL);

    if (is_null && spec->has_precision)
        str = "";
    else if (is_null)
        str = "(null)";
    params.str_len = my_strlen(str);
    params.prec_pad = 0;
    adjust_precision(spec, &params.str_len, &params.prec_pad, str);
    total_len = params.str_len + params.prec_pad;
    params.width_pad = (spec->width > total_len) ? spec->width - total_len : 0;
    print_str_with_padding(spec, str, count, &params);
}

static void handle_wide_str(format_spec_t *spec, va_list args, int *count)
{
    wchar_t *wstr = va_arg(args, wchar_t *);
    wchar_t null_wstr[] = {L'(', L'n', L'u', L'l', L'l', L')', 0};
    int byte_len = 0;
    wstr_print_info_t info;
    int char_bytes = 0;

    if (wstr == NULL)
        wstr = null_wstr;
    info.wstr = wstr;
    info.chars_to_print = 0;
    for (int i = 0; wstr[i] != 0; i++) {
        char_bytes = wchar_n_bytes(wstr[i]);
        if (spec->has_precision && (byte_len + char_bytes) > spec->precision)
            break;
        byte_len += char_bytes;
        info.chars_to_print++;
    }
    info.padding = (spec->width > byte_len) ? spec->width - byte_len : 0;
    info.flags = spec->flags;
    print_wstr_with_padding(&info, count);
}

int handle_str(format_spec_t *spec, va_list args)
{
    int count = 0;

    if (spec->length == 'l')
        handle_wide_str(spec, args, &count);
    else
        handle_normal_str(spec, args, &count);
    return count;
}
