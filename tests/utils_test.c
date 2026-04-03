/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** utils_tests
*/

#include "op.h"
#include "criterion/criterion.h"

Test(clean_line, null_string)
{
    char *temp = clean_line(NULL);

    cr_assert_eq(temp, NULL);
}

Test(clean_line, basic_string)
{
    char *temp = clean_line("\t Hello");

    cr_assert_str_eq(temp, "Hello");
}

Test(close_and_return_null, basic_case)
{
    FILE *stream = fopen("tests/jon.s", "r");
    char *temp = "test";

    temp = close_and_ret_null(stream);
    cr_assert_eq(temp, NULL);
}

Test(free_return, basic_case)
{
    char *temp = calloc(1, sizeof(char));
    void *test = free_return(temp);

    cr_assert_eq(test, NULL);
}

Test(get_final_name, null_string)
{
    char *temp = get_final_name(NULL);

    cr_assert_eq(temp, NULL);
}

Test(get_final_name, empty_string)
{
    char *temp = get_final_name("\0");

    cr_assert_eq(temp, NULL);
}

Test(get_final_name, basic_case)
{
    char *temp = get_final_name("jon.s");

    cr_assert_str_eq(temp, "jon.cor");
}

Test(my_calloc, no_size)
{
    char *test = my_calloc(0, sizeof(char));
    char *test2 = my_calloc(1, 0);

    cr_assert_eq(test, NULL);
    cr_assert_eq(test2, NULL);
}

Test(my_calloc, basic_case)
{
    char *test = my_calloc(1, sizeof(char));

    cr_assert_neq(test, NULL);
}

Test(my_getnbr, null_string)
{
    int test = my_getnbr(NULL);

    cr_assert_eq(test, 0);
}

Test(my_getnbr, empty_string)
{
    int test = my_getnbr("\0");

    cr_assert_eq(test, 0);
}

Test(my_getnbr, no_nbr_string)
{
    int test = my_getnbr("Hello");

    cr_assert_eq(test, 0);
}

Test(my_getnbr, basic_case)
{
    int test = my_getnbr("67");

    cr_assert_eq(test, 67);
}

Test(my_getnbr, negative_nbr)
{
    int test = my_getnbr("-67");

    cr_assert_eq(test, -67);
}
