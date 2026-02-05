/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-secured-14
** File description:
** test_functional.c
*/

#include <criterion/criterion.h>
#include "../include/hashtable.h"

Test(hashtable, insert_and_search)
{
    hashtable_t *ht = new_hashtable(&hash, 10);
    char *val;

    int ret = ht_insert(ht, "Key1", "Value1");
    cr_assert_eq(ret, 0, "Insert should succeed");

    val = ht_search(ht, "Key1");
    cr_assert_str_eq(val, "Value1", "Should return correct value");

    delete_hashtable(ht);
}

Test(hashtable, search_not_found)
{
    hashtable_t *ht = new_hashtable(&hash, 10);

    char *val = ht_search(ht, "Unknown");
    cr_assert_null(val, "Should return NULL");

    delete_hashtable(ht);
}

Test(hashtable, delete_entry)
{
    hashtable_t *ht = new_hashtable(&hash, 10);
    char *val;
    int ret = 0;

    ht_insert(ht, "KeyToKill", "Value");
    ret = ht_delete(ht, "KeyToKill");
    cr_assert_eq(ret, 0, "Delete should succeed");

    val = ht_search(ht, "KeyToKill");
    cr_assert_null(val, "Entry should not exist");

    delete_hashtable(ht);
}

Test(hashtable, update_existing_entry)
{
    hashtable_t *ht = new_hashtable(&hash, 10);
    char *val;

    ht_insert(ht, "Key1", "OldValue");
    ht_insert(ht, "Key1", "NewValue");
    val = ht_search(ht, "Key1");
    cr_assert_str_eq(val, "NewValue", "Value should be updated");

    delete_hashtable(ht);
}
