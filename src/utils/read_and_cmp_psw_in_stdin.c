/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** read_and_cmp_psw_in_stdin.c
*/

#include "../../include/my.h"

static void handle_input_result(data_t *data, ssize_t read_bytes)
{
    int len_pass = 0;

    if (read_bytes == -1) {
        if (data->put_password) {
            free(data->put_password);
            data->put_password = NULL;
        }
        return;
    }
    len_pass = strlen(data->put_password);
    if (len_pass > 0 && data->put_password[len_pass - 1] == '\n')
        data->put_password[len_pass - 1] = '\0';
}

static void get_input(data_t *data, int is_tty)
{
    struct termios old_t;
    struct termios new_t;
    size_t len = 0;
    ssize_t read_bytes = 0;

    if (is_tty) {
        tcgetattr(STDIN_FILENO, &old_t);
        new_t = old_t;
        new_t.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    }
    read_bytes = getline(&data->put_password, &len, stdin);
    if (is_tty) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
        fprintf(stderr, "\n");
    }
    handle_input_result(data, read_bytes);
}

void read_and_cmp_psw_in_stdin(data_t *data)
{
    int is_tty = isatty(STDIN_FILENO);

    for (int i = 0; i < 3; i++) {
        if (i != 0)
            fprintf(stderr, "Sorry, try again.\n");
        fprintf(stderr, "[my_sudo] password for [%s]: ", data->my_user_name);
        get_input(data, is_tty);
        if (data->put_password == NULL)
            return;
        if (strcmp(crypt(data->put_password, data->get_hashed_pass),
                data->get_hashed_pass) == 0) {
            data->good_pass = true;
            return;
        }
    }
    fprintf(stderr, "my_sudo: 3 incorrect password attempts\n");
}
