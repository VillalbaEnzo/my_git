/*
** EPITECH PROJECT, 2025
** pokemon [WSL: Ubuntu-24.04]
** File description:
** game_loop.c
*/

#include "my.h"

static bool play_turn(pokemon_t *attacker, pokemon_t *defender)
{
    int damage = 0;

    damage = attacker->attack > 0 ? rand() % (attacker->attack + 1) : 0;
    printf("%s attacks for %i damage\n", attacker->name, damage);
    printf("%s blocks %i damage\n", defender->name, defender->defense);
    damage = (damage - defender->defense < 0) ?
        0 : (damage - defender->defense);
    defender->heal -= damage;
    printf("%s loses %i health (%i left)\n", defender->name, damage,
        defender->heal < 0 ? 0 : defender->heal);
    if (defender->heal <= 0) {
        printf("%s is KO\n", defender->name);
        return false;
    }
    return true;
}

static void combat(pokemon_t *one, pokemon_t *two)
{
    if (!play_turn(one, two))
        return;
    if (!play_turn(two, one))
        return;
}

bool game_loop(pokemon_t *one, pokemon_t *two)
{
    if (!one || !two)
        return false;
    while (one->heal > 0 && two->heal > 0)
        (void)(one->speed < two->speed ? combat(two, one) : combat(one, two));
    printf("%s wins the fight!\n", (one->heal > 0 ? one->name : two->name));
    return true;
}
