/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_instruction.c
*/

#include "op.h"

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

static void set_arg_val(arg_t *arg, char *str)
{
    int i = 0;

    if (str[i] == 'r' || str[i] == DIRECT_CHAR)
        i++;
    if (str[i] == LABEL_CHAR) {
        i++;
        arg->label = my_calloc(my_strlen(str + i) + 1, sizeof(char));
        my_strcpy(arg->label, str + i);
        arg->distance = 0;
    } else {
        arg->label = NULL;
        arg->distance = my_getnbr(str + i);
    }
}

static int check_inst_for_cal(inst_t *inst)
{
    if (inst->opcode == 1 || inst->opcode == 9 ||
        inst->opcode == 12 || inst->opcode == 15) {
        inst->coding_byte = 0;
        return 1;
    }
    return 0;
}

static void calc_coding_byte(inst_t *inst)
{
    int cb = 0;

    if (check_inst_for_cal(inst))
        return;
    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        switch (inst->args[i].type) {
            case T_REG:
                cb = cb | (1 << (6 - i * 2));
                break;
            case T_DIR:
                cb = cb | (2 << (6 - i * 2));
                break;
            case T_IND:
                cb = cb | (3 << (6 - i * 2));
                break;
            default:
                break;
        }
    }
    inst->coding_byte = cb;
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
        set_arg_val(&(inst->args[i]), arg);
    }
    calc_coding_byte(inst);
    free_array((void **)array);
}

inst_t *parse_instruction(char *ptr)
{
    inst_t *inst = NULL;
    int word_len = 0;

    if (ptr[0] == '\0')
        return NULL;
    inst = find_inst(ptr);
    if (!inst)
        return NULL;
    while (ptr[word_len] != ' ' && ptr[word_len] != '\t' &&
        ptr[word_len] != '\0') {
        word_len++;
    }
    ptr = clean_line(ptr + word_len);
    parse_args(ptr, inst);
    return inst;
}
