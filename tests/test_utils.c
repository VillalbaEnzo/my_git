/*
** EPITECH PROJECT, 2025
** Secured Tests
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include "../include/hashtable.h"

Test(hashtable, create_table)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    cr_assert_not_null(ht, "La table ne devrait pas être NULL");
    cr_assert_not_null(ht->buckets, "Le tableau interne ne devrait pas être NULL");
    cr_assert_eq(ht->len, 10, "La taille stockée devrait être 10");
    delete_hashtable(ht);
}

Test(hashtable, create_error)
{
    hashtable_t *ht = new_hashtable(&hash, -5);
    cr_assert_null(ht, "La création avec taille négative devrait renvoyer NULL");

    ht = new_hashtable(NULL, 10);
    cr_assert_null(ht, "La création sans fonction de hash devrait renvoyer NULL");
}

Test(hashtable, hash_consistency)
{
    int h1 = hash("test", 10);
    int h2 = hash("test", 10);
    int h3 = hash("autre", 10);

    cr_assert_eq(h1, h2, "Le hash doit être déterministe (toujours le même pour la même clé)");
    cr_assert_neq(h1, h3, "Deux clés différentes devraient avoir des hash différents (idéalement)");
}
