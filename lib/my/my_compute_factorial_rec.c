/*
** EPITECH PROJECT, 2025
** G-CPE-100-LYN-1-1-cpoolday05-48
** File description:
** my_compute_factorial_rec.c
*/

int my_compute_factorial_rec(int nb)
{
    if (nb >= 13 || nb < 0 || nb > 2147483647)
        return 0;
    if (nb == 0 || nb == 1)
        return 1;
    return nb * my_compute_factorial_rec(nb - 1);
}
