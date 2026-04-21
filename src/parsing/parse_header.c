/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** parse_header
*/
#include "op.h"

static int line_type(char *line)
{
    if (my_strncmp(line, NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)) == 0)
        return 1;
    if (my_strncmp(line, COMMENT_CMD_STRING,
            my_strlen(COMMENT_CMD_STRING)) == 0)
        return 2;
    return 0;
}

static int get_position(char **l_tokens, char *target_type)
{
    if (!l_tokens)
        return -1;
    for (int i = 0; l_tokens[i] != NULL; i++) {
        if (my_strcmp(l_tokens[i], target_type) == 0)
            continue;
        if (l_tokens[i][0] != COMMENT_CHAR)
            return i;
    }
    return -1;
}

int get_champ_name(header_t *header, char *line)
{
    char **l_tokens = NULL;
    int name_pos = 0;

    l_tokens = str_to_token_array_delim(line, ' ');
    if (l_tokens == NULL)
        return -1;
    name_pos = get_position(l_tokens, NAME_CMD_STRING);
    if (name_pos == -1 || my_strlen(l_tokens[name_pos]) > PROG_NAME_LENGTH) {
        free_array((void **)l_tokens);
        return -1;
    }
    my_strcpy(header->prog_name, l_tokens[name_pos]);
    free_array((void **)l_tokens);
    return 0;
}

int get_comment(header_t *header, char *line)
{
    char **l_tokens = NULL;
    int name_pos = 0;

    l_tokens = str_to_token_array_delim(line, ' ');
    if (l_tokens == NULL)
        return -1;
    name_pos = get_position(l_tokens, COMMENT_CMD_STRING);
    if (name_pos == -1 || my_strlen(l_tokens[name_pos]) > COMMENT_LENGTH) {
        free_array((void **)l_tokens);
        return -1;
    }
    my_strcpy(header->comment, l_tokens[name_pos]);
    free_array((void **)l_tokens);
    return 0;
}

int get_header_info(header_t *header, char *line)
{
    switch (line_type(line)) {
        case 1:
            return get_champ_name(header, line);
        case 2:
            return get_comment(header, line);
        case 0:
            return -1;
    }
    return -1;
}

header_t *parse_header(FILE *fstream)
{
    header_t *header = NULL;
    char *line = NULL;

    if (fstream == NULL)
        return NULL;
    header = my_calloc(1, sizeof(header_t));
    if (header == NULL)
        return close_and_ret_null(fstream);
    line = read_line(fstream, line, true);
    while (line != NULL) {
        if (get_header_info(header, clean_line(line)) == -1) {
            free(header);
            return close_and_ret_null(fstream);
        }
        free(line);
        line = NULL;
        line = read_line(fstream, line, true);
    }
    return header;
}
