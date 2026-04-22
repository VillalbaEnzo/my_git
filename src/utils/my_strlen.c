/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_strlen
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
