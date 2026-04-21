/*
** EPITECH PROJECT, 2026
** robotfactory [WSL: Ubuntu]
** File description:
** parse_file
*/

#include "op.h"

static bool fill_parse_data(FILE *fstream, data_t *temp, const char *filename)
{
    temp->header = parse_header(fstream);
    if (temp->header == NULL)
        return false;
    temp->filename = get_final_name(filename);
    parse_body(fstream, temp);
    if (!temp->filename || temp->inst == NULL) {
        fclose(fstream);
        return false;
    }
    handle_label(temp);
    fclose(fstream);
    return true;
}

data_t *parse_file(const char *filename)
{
    FILE *fstream = fopen(filename, "r");
    data_t *temp = NULL;

    if (!fstream)
        return NULL;
    temp = my_calloc(1, sizeof(data_t));
    if (!temp) {
        fclose(fstream);
        return NULL;
    }
    if (!fill_parse_data(fstream, temp, filename)) {
        free_data(temp);
        return NULL;
    }
    return temp;
}
