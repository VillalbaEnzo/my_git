/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-secured-14
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include "../include/hashtable.h"

Test(hashtable, create_table)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    cr_assert_not_null(ht, "Table should not be NULL");
    cr_assert_not_null(ht->buckets, "Buckets should not be NULL");
    cr_assert_eq(ht->len, 10, "Size should be 10");

    delete_hashtable(ht);
}

Test(hashtable, create_error)
{
    hashtable_t *ht = new_hashtable(&hash, -5);
    cr_assert_null(ht, "Negative size should fail");

    ht = new_hashtable(NULL, 10);
    cr_assert_null(ht, "NULL hash function should fail");
}

Test(hashtable, hash_consistency)
{
    int h1 = hash("test", 10);
    int h2 = hash("test", 10);
    int h3 = hash("other", 10);

    cr_assert_eq(h1, h2, "Hash should be deterministic");
    cr_assert_neq(h1, h3, "Different keys should differ");
}
