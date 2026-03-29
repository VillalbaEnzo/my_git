/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** handler_write.c
*/

#include "op.h"

static bool write_magic_nbr(FILE *file)
{
    int magic = COREWAR_EXEC_MAGIC;
    size_t len;

    magic = (int)swap_endian_int((unsigned int)magic);
    len = fwrite(&magic, sizeof(magic), 1, file);
    if (len == 0)
        return false;
    return true;
}

static bool write_name(FILE *file, data_t *data)
{
    size_t len;

    len = fwrite(data->header->prog_name, sizeof(char),
        data->header->prog_size, file);
    if (len == 0)
        return false;
    return true;
}

bool write_header(data_t *data)
{
    FILE *file = fopen(data->filename, "wb");

    if (!file)
        return false;
    if (!write_magic_nbr(file) || !write_name(file, data)) {
        fclose(file);
        return false;
    }
    return true;
}
//https://koor.fr/C/cstdio/fopen.wp
