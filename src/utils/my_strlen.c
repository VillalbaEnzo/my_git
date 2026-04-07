/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_strlen
*/

/**
 * Get length of a string
 * @param str string to get length of
 * @return Lenght of string, 0 if no string
 */
int my_strlen(char const *str)
{
    int count = 0;

    if (!str)
        return count;
    for (int i = 0; str[i] != '\0'; i++)
        count++;
    return count;
}
