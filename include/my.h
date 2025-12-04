/*
** EPITECH PROJECT, 2025
** G-PSU-100-LYN-1-1-mysudo-39
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #define _XOPEN_SOURCE
    #define _GNU_SOURCE
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <grp.h>
    #include <sys/types.h>
    #include <termios.h>

typedef enum flag_e {
    H_FLAG,
    U_FLAG,
    G_FLAG,
    U_AND_G_FLAG,
    EMPTY
} flag_t;

typedef struct data_s {
    int argc;
    char **argv;
    char **command;
    char *user_name;
    char *group_name;
    char *my_user_name;
    char *my_group_name;
    char **in_group;
    char **in_group_id;
    int my_uid;
    int my_gid;
    int uid;
    int gid;
    flag_t flags;
    char *put_password;
    char *get_hashed_pass;
    bool good_pass;
} data_t;

typedef struct parser_s {
    char *buf;
    char ***array;
    char **double_array;
    int str_len;
    int buf_idx;
} parser_t;

void free_prog(data_t *data);
void free_struct_s(parser_t *s);

void init(data_t *data, int argc, char **argv);
void init_paser_struct(parser_t *s);

bool load_file_and_fill_buf(parser_t *s, char *filepath);
bool file_parser(parser_t *s, int nbr_arg);
bool get_user_group_info(data_t *data);
char *my_strdup(const char *c);
char *my_strndup(const char *c, int n);
bool fill_d_array(parser_t *s);
void fill_in_group_id(data_t *data, parser_t *s);
void read_and_cmp_psw_in_stdin(data_t *data);

void find_user_id(data_t *data, parser_t *s);
void find_group_id(data_t *data, parser_t *s);
void find_group_id_flag_u(data_t *data, parser_t *s);
void find_my_user_name(data_t *data, parser_t *s);
void find_my_group_name(data_t *data, parser_t *s);

bool parser(data_t *data);
bool auth(data_t *data);
bool execute(data_t *data);

#endif
