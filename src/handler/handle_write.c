/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** handler_write.c
*/

#include "op.h"

bool write_header(data_t *data, FILE *file)
{
    size_t len = 0;

    if (!file)
        return false;
    data->header->magic = swap_endian_int(COREWAR_EXEC_MAGIC);
    data->header->prog_size = swap_endian_int(data->header->prog_size);
    len = fwrite(data->header, sizeof(header_t), 1, file);
    if (len != 1) {
        fclose(file);
        return false;
    }
    return true;
}

static size_t write_ind_arg(arg_t *curr_arg, FILE *file)
{
    curr_arg->distance = swap_endian_short(curr_arg->distance);
    return fwrite(&curr_arg->distance, IND_SIZE, 1, file);
}

static size_t write_dir_arg(arg_t *curr_arg, FILE *file, bool is_ind)
{
    if (is_ind)
        return write_ind_arg(curr_arg, file);
    else {
        curr_arg->distance = swap_endian_int(curr_arg->distance);
        return fwrite(&curr_arg->distance, DIR_SIZE, 1, file);
    }
}

static bool write_args(inst_t *curr_inst, FILE *file)
{
    size_t len = 0;
    bool is_ind = is_index(curr_inst->opcode);

    for (int i = 0; curr_inst->args[i].type != 0; i++) {
        switch (curr_inst->args[i].type) {
            case T_REG:
                len = fwrite(&curr_inst->args[i].distance,
                    sizeof(char), 1, file);
                break;
            case T_DIR:
                len = write_dir_arg(&curr_inst->args[i], file, is_ind);
                break;
            case T_IND:
                len = write_ind_arg(&curr_inst->args[i], file);
                break;
        }
        if (len != 1)
            return false;
    }
    return true;
}

bool write_instr(data_t *data, FILE *file)
{
    size_t len = 0;

    if (!file)
        return false;
    for (inst_t *temp = data->inst; temp != NULL; temp = temp->next) {
        if (fwrite(&temp->opcode, sizeof(char), 1, file) != 1)
            return false;
        if (temp->coding_byte != 0)
            len = fwrite(&temp->coding_byte, sizeof(char), 1, file);
        if (len != 1)
            return false;
        if (write_args(temp, file) == false)
            return false;
    }
    return true;
}

bool write_file(data_t *data)
{
    FILE *file = fopen(data->filename, "wb");

    if (write_header(data, file) == false)
        return false;
    if (write_instr(data, file) == false) {
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}
//https://koor.fr/C/cstdio/fopen.wp
