/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** parse_file
*/

#include "op.h"

data_t *pars_file(const char *filename)
{
    data_t *temp = malloc(sizeof(data_t));
    FILE *fstream = fopen(filename, "r");

    if (!temp) {
        if (fstream)
            fclose(fstream);
        return NULL;
    }
    temp->header = parse_header(fstream);
    if (!temp->header)
        return free_return(temp);
    temp->filename = get_final_name(filename);
    if (!temp->filename) {
        return free_return(temp);
    }
    parse_body(fstream);
    return temp;
}
/* --ICI-- */
