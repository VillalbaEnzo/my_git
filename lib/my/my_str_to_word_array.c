/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-21
** File description:
** my_str_to_word_array.c
*/

#include <stdlib.h>

int validator(char c)
{
    if ((c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}

static void update(int *count, int *in, char c)
{
    if (validator(c)) {
        if (*in == 0) {
            (*count)++;
            *in = 1;
        }
    } else {
        *in = 0;
    }
}

int count_words(char const *str)
{
    int count = 0;
    int in = 0;

    for (int i = 0; str[i]; i++)
        update(&count, &in, str[i]);
    return count;
}

static int get_valid_word_len(char const *str, int i)
{
    int len = 0;

    for (int j = i; str[j] && validator(str[j]); j++)
        len++;
    return (len);
}

static int skip_non_alnum(char const *str, int i)
{
    while (str[i] && !validator(str[i]))
        i++;
    return (i);
}

static void free_p(char **arr, int idx, int *val)
{
    if (!arr[idx]) {
        for (int k = 0; k < idx; k++)
            free(arr[k]);
    }
    *val = -1;
}

static char *allocate_memory_word(char const *str, int start, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));
    int j = 0;

    if (!word)
        return (NULL);
    for (; j < len; j++)
        word[j] = str[start + j];
    word[j] = '\0';
    return word;
}

static int fill_array(char **arr, char const *str, int words)
{
    int idx = 0;
    int val = 0;
    int i = 0;
    int len = 0;

    while (str[i] && idx < words) {
        i = skip_non_alnum(str, i);
        if (!str[i])
            break;
        len = get_valid_word_len(str, i);
        arr[idx] = allocate_memory_word(str, i, len);
        if (!arr[idx]) {
            free_p(arr, idx, &val);
            break;
        }
        idx++;
        i += len;
    }
    arr[idx] = NULL;
    return val;
}

char **my_str_to_word_array(char const *str)
{
    char **arr;
    int words;

    if (!str)
        return (NULL);
    words = count_words(str);
    arr = malloc(sizeof(char *) * (words + 1));
    if (!arr)
        return (NULL);
    if (fill_array(arr, str, words) == -1) {
        free(arr);
        return (NULL);
    }
    return (arr);
}
