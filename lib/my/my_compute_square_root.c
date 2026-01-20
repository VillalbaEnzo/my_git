/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-48
** File description:
** my_compute_square_root.c
*/

int my_compute_square_root(int nb)
{
    int i = 0;

    if (nb < 0)
        return 0;
    if (nb == 0 || nb == 1)
        return nb;
    while (i * i <= nb) {
        if (i * i == nb)
            return i;
        i++;
        if (i > 46340)
            break;
    }
    return 0;
}
