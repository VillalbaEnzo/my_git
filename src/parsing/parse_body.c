/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_body.c
*/

#include "op.h"

static void clear_com(char *line)
{
    int idx = 0;

    if (!line)
        return;
    while (line[idx] != '\0' && line[idx] != COMMENT_CHAR)
        idx++;
    if (line[idx] == COMMENT_CHAR)
        line[idx] = '\0';
}

static inst_t *find_inst(char *line)
{
    int len = 0;
    inst_t *temp = NULL;

    while (line[len] != ' ' && line[len] != '\t' && line[len] != '\0')
        len++;
    if (len == 0)
        return NULL;
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (my_strncmp(op_tab[i].mnemonique, line, len) != 0 ||
            op_tab[i].mnemonique[len] != '\0')
            continue;
        temp = my_calloc(1, sizeof(inst_t));
        if (temp)
            temp->opcode = op_tab[i].code;
        break;
    }
    return temp;
}

static void set_arg_type(arg_t *arg, char *str)
{
    switch (str[0]) {
        case 'r':
            arg->type = T_REG;
            break;
        case DIRECT_CHAR:
            arg->type = T_DIR;
            break;
        default:
            arg->type = T_IND;
            break;
    }
}

static void parse_args(char *args_line, inst_t *inst)
{
    char **array = NULL;
    char *arg = NULL;

    if (!args_line || args_line[0] == '\0')
        return;
    array = str_to_token_array_delim(args_line, SEPARATOR_CHAR);
    if (!array)
        return;
    for (int i = 0; array[i] != NULL && i < MAX_ARGS_NUMBER; i++) {
        arg = clean_line(array[i]);
        set_arg_type(&(inst->args[i]), arg);
    }
    free_array((void **)array);
}

static void process_line(char *ptr)
{
    inst_t *inst = NULL;
    int word_len = 0;

    if (ptr[0] == '\0')
        return;
    inst = find_inst(ptr);
    if (!inst)
        return;
    while (ptr[word_len] != ' ' && ptr[word_len] != '\t' &&
        ptr[word_len] != '\0') {
        word_len++;
    }
    ptr = clean_line(ptr + word_len);
    parse_args(ptr, inst);
}

void parse_body(FILE *file)
{
    char *line = NULL;
    char *ptr = NULL;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        ptr = clean_line(line);
        process_line(ptr);
        free(line);
        line = NULL;
        line = read_line(file, line, false);
    }
}
