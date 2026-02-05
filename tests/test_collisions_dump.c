/*
** EPITECH PROJECT, 2025
** G-CPE-110-LYN-1-1-secured-14
** File description:
** test_collisions_dump.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/hashtable.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

int mock_hash_always_zero(char *key, int len)
{
    (void)key;
    (void)len;
    return 0;
}

Test(hashtable, handle_collisions)
{
    hashtable_t *ht = new_hashtable(&mock_hash_always_zero, 5);

    ht_insert(ht, "A", "ValA");
    ht_insert(ht, "B", "ValB");

    cr_assert_str_eq(ht_search(ht, "A"), "ValA", "Should find A");
    cr_assert_str_eq(ht_search(ht, "B"), "ValB", "Should find B");

    ht_delete(ht, "A");
    cr_assert_null(ht_search(ht, "A"), "A should be deleted");
    cr_assert_str_eq(ht_search(ht, "B"), "ValB", "B should remain");

    delete_hashtable(ht);
}

Test(hashtable, dump_display, .init = redirect_all_std)
{
    hashtable_t *ht = new_hashtable(&mock_hash_always_zero, 2);

    ht_insert(ht, "Test", "Value");
    ht_dump(ht);

    cr_assert_stdout_eq_str(
        "[0]:\n> 0 - Value\n[1]:\n",
        "Dump output should match"
    );
}
