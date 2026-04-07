/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** handler_write.c
*/

#include "op.h"

bool write_header(data_t *data)
{
    FILE *file = fopen(data->filename, "wb");
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
    fclose(file);
    return true;
}
//https://koor.fr/C/cstdio/fopen.wp
