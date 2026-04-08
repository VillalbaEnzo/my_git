/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** parse_file
*/

#include "op.h"

data_t *parse_file(const char *filename)
{
    data_t *temp = NULL;
    FILE *fstream = fopen(filename, "r");

    if (!fstream)
        return NULL;
    temp = my_calloc(1, sizeof(data_t));
    if (!temp) {
        fclose(fstream);
        return NULL;
    }
    temp->header = parse_header(fstream);
    temp->filename = get_final_name(filename);
    parse_body(fstream, temp);
    if (!temp->header || !temp->filename || temp->inst == NULL) {
        fclose(fstream);
        return free_return(temp);
    }
    handle_label(temp);
    fclose(fstream);
    return temp;
}
/* --ICI-- */
