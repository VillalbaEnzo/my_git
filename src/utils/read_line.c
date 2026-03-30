/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** read_line
*/

#include "op.h"

/**
 * Reads current line of stream
 * @param fstream file stream to read from
 * @param line string to write in
 * @return NULL if error or EOF, line otherwise
 */
char *read_line(FILE *fstream, char *line, bool stop_on_nl)
{
    size_t trash = 0;
    ssize_t bytes_read = 0;

    bytes_read = getline(&line, &trash, fstream);
    if (bytes_read == -1 || (line[0] == '\n' && stop_on_nl == true)) {
        free(line);
        return NULL;
    } else {
        if (line[bytes_read - 1] == '\n')
            line[bytes_read - 1] = '\0';
        return line;
    }
}
