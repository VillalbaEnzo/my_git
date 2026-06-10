/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** str_to_word_array.c
*/

#include "my.h"


static int is_delim(char c, char *delims)
{
    if (!delims)
        return 0;
    for (int i = 0; delims[i]; i++) {
        if (c == delims[i])
            return 1;
    }
    return 0;
}

static int count_words(char *str, char *delims)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (!is_delim(str[i], delims) && !in_word) {
            in_word = 1;
            count++;
        }
        if (is_delim(str[i], delims))
            in_word = 0;
    }
    return count;
}

static char *word_dup(char *str, int start, int end)
{
    int length = end - start;
    char *word = malloc(sizeof(char) * (length + 1));

    if (!word)
        return NULL;
    for (int i = 0; i < length; i++)
        word[i] = str[start + i];
    word[length] = '\0';
    return word;
}

static char **fill_array_str(char *str, char *delims, char **array)
{
    int j = 0;
    int start = -1;

    for (int i = 0; str[i]; i++) {
        if (!is_delim(str[i], delims) && start == -1)
            start = i;
        if (start == -1 || (!is_delim(str[i + 1], delims) && str[i + 1]))
            continue;
        array[j] = word_dup(str, start, i + 1);
        if (!array[j])
            break;
        j++;
        start = -1;
    }
    array[j] = NULL;
    if (start != -1) {
        free_double_array(array);
        return NULL;
    }
    return array;
}

char **str_to_word_array(char *str, char *delims)
{
    int words = 0;
    char **array = NULL;

    if (!str)
        return NULL;
    words = count_words(str, delims);
    array = malloc(sizeof(char *) * (words + 1));
    if (!array)
        return NULL;
    return fill_array_str(str, delims, array);
}
