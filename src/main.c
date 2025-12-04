/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-organized-33
** File description:
** main.c
*/

#include "./include/my.h"

int main(void)
{
    context_t *ctx = malloc(sizeof(context_t));

    if (!ctx)
        return 84;
    ctx->head = NULL;
    ctx->next_id = 0;
    if (workshop_shell(ctx) == 84) {
        free(ctx);
        return 84;
    }
    free(ctx);
    return 0;
}
