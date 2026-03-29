/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** close_and_return
*/

#include "op.h"

/**
 * Close file stream and returns NULL (error handling purposes)
 * @param fstream file stream to close
 * @return NULL
 */
void *close_and_ret_null(FILE *fstream)
{
    fclose(fstream);
    return NULL;
}
