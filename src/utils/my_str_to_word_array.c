/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday08-8
** File description:
** my_str_to_word_array.c
*/

#include "../../include/my.h"

static char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n) {
        if (src[i] != '\0')
            dest[i] = src[i];
        else
            dest[i] = '\0';
        i++;
    }
    return dest;
}

static int is_alphanum(char x)
{
    if ((x >= 'a' && x <= 'z')
        || (x >= 'A' && x <= 'Z')
        || (x >= '0' && x <= '9')) {
        return 1;
    }
    return 0;
}

static int count_words(char const *str)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    while (str[i] != '\0') {
        if (is_alphanum(str[i]) == 1 && in_word == 0) {
            in_word = 1;
            count++;
        }
        if (is_alphanum(str[i]) == 0 && in_word == 1)
            in_word = 0;
        i++;
    }
    return count;
}

char **my_str_to_word_array(char const *str)
{
    int words = count_words(str);
    int counter = 0;
    int str_index = 0;
    char **array = malloc(sizeof(char *) * (words + 1));

    for (int words_count = 0; words_count < words; words_count++) {
        while (is_alphanum(str[str_index]) == 0) {
            str_index++;
        }
        counter = 0;
        while (is_alphanum(str[str_index + counter]) == 1) {
            counter++;
        }
        array[words_count] = malloc(sizeof(char) * (counter + 1));
        my_strncpy(array[words_count], str + str_index, counter);
        array[words_count][counter] = '\0';
        str_index += counter;
    }
    array[words] = NULL;
    return array;
}
