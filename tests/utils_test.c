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

Test(my_str_to_token_array, null_string)
{
    char **array = str_to_token_array_delim(NULL, ' ');

    cr_assert_eq(array, NULL);
}

Test(my_str_to_token_array, no_tokens)
{
    char *test = "Hello Everyone";
    char **array = str_to_token_array_delim(test, '\n');

    cr_assert_str_eq(array[0], test);
}

Test(my_str_to_token_array, basic_case)
{
    char *test = "Hello Everyone I Am Groot";
    char **array = str_to_token_array_delim(test, ' ');
    char *expected[6] = {"Hello", "Everyone", "I", "Am", "Groot"};

    for (int i = 0; i < 5; i++)
        cr_assert_str_eq(array[i], expected[i]);
}

Test(my_str_to_token_array, quoted_tokens)
{
    char *test = "Hello \"Everyone I Am Groot\"";
    char **array = str_to_token_array_delim(test, ' ');
    char *expected[2] = {"Hello", "Everyone I Am Groot"};

    for (int i = 0; i < 2; i++)
        cr_assert_str_eq(array[i], expected[i]);
}

Test(my_strcmp, null_string)
{
    char *test1 = NULL;
    char *test2 = "Bonjour";
    char *test3 = "Bonsoir";
    char *test4 = NULL;
    int res1 = my_strcmp(test1, test2);
    int res2 = my_strcmp(test3, test4);

    cr_assert_eq(res1, 84);
    cr_assert_eq(res2, 84);
}

Test(my_strcmp, inferior)
{
    char *s_test_1 = "aaa";
    char *s_test_2 = "bbbbbb";
    int expected = my_strcmp(s_test_1, s_test_2);

    cr_assert_eq(expected, -1);
}

Test(my_strcmp, superior)
{
    char *s_test_1 = "aaa";
    char *s_test_2 = "bbbbbb";
    int expected = my_strcmp(s_test_2, s_test_1);

    cr_assert_eq(expected, 1);
}

Test(my_strcmp, equal)
{
    char *test1 = "bonjour";
    char *test2 = "bonjour";
    int expected = my_strcmp(test1, test2);

    cr_assert_eq(expected, 0);
}

Test(my_strcmp, almost_equal)
{
    char *test1 = "bonjourbonj";
    char *test2 = "bonjourbo";
    int expected = my_strcmp(test1, test2);

    cr_assert_eq(expected, 1);
}

Test(read_line, null_stream)
{
    char *test = read_line(NULL, NULL, false);

    cr_assert_eq(test, NULL);
}

Test(read_line, basic_case)
{
    FILE *test_stream = fopen("tests/jon.s", "r");
    char *line = NULL;

    line = read_line(test_stream, line, false);
    cr_assert_str_eq(line, ".name \"Jon Snow\"");
}
