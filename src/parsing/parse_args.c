/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_args.c
*/

#include "op.h"

static bool check_inst_for_cal(inst_t *inst)
{
    if (inst->opcode == 1 || inst->opcode == 9 ||
        inst->opcode == 12 || inst->opcode == 15) {
        inst->coding_byte = 0;
        return true;
    }
    return false;
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

static int calc_args_size(inst_t *inst)
{
    int arg_size = 0;
    bool is_ind = is_index(inst->opcode);

    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        switch (inst->args[i].type) {
            case T_REG:
                arg_size += REG_SIZE;
                break;
            case T_DIR:
                arg_size += (is_ind ? IND_SIZE : DIR_SIZE);
                break;
            case T_IND:
                arg_size += IND_SIZE;
                break;
        }
    }
    return arg_size;
}

static bool set_arg_type(arg_t *arg, char *str)
{
    if (!str || str[0] == '\0')
        return false;
    if (str[0] == 'r') {
        arg->type = T_REG;
        return true;
    }
    if (str[0] == DIRECT_CHAR) {
        arg->type = T_DIR;
        return true;
    }
    if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-' ||
        str[0] == LABEL_CHAR) {
        arg->type = T_IND;
        return true;
    }
    return false;
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

static bool is_args_valid(inst_t *inst)
{
    int count = 0;

    for (int i = 0; inst->args[i].type != 0; i++) {
        if ((inst->args[i].type & op_tab[inst->opcode].type[i])
            != inst->args[i].type)
            return false;
        if (inst->args[i].type == T_REG && (inst->args[i].distance < 1
                || inst->args[i].distance > REG_NUMBER))
            return false;
        count++;
    }
    if (count != op_tab[inst->opcode].nbr_args)
        return false;
    return true;
}

static bool parse_and_fill_args(char **array, inst_t *inst)
{
    char *arg = NULL;

    for (int i = 0; array[i] != NULL && i < MAX_ARGS_NUMBER; i++) {
        arg = clean_line(array[i]);
        if (set_arg_type(&(inst->args[i]), arg) == false)
            return false;
        set_arg_val(&(inst->args[i]), arg);
    }
    return true;
}

bool parse_args(char *args_line, inst_t *inst)
{
    char **array = NULL;

    inst->total = (check_inst_for_cal(inst)) ? 1 : 2;
    if (!args_line || args_line[0] == '\0')
        return false;
    array = str_to_token_array_delim(args_line, SEPARATOR_CHAR);
    if (!array)
        return false;
    if (!parse_and_fill_args(array, inst)) {
        free_array((void **)array);
        return false;
    }
    if (!is_args_valid(inst)) {
        free_array((void **)array);
        return false;
    }
    inst->total += calc_args_size(inst);
    calc_coding_byte(inst);
    free_array((void **)array);
    return true;
}
