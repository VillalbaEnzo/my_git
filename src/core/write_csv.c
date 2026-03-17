/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** write_csv
*/

#include "dataframe.h"

static int write_header(dataframe_t *df, FILE *new_file)
{
    int is_error = 0;

    for (size_t i = 0; i < df->header->count; i++) {
        if (i == df->header->count - 1)
            is_error = fprintf(new_file, "%s", df->header->columns[i].name);
        else
            is_error = fprintf(new_file, "%s%s", df->header->columns[i].name,
                df->separator);
        if (is_error < 0)
            return 1;
    }
    fprintf(new_file, "\n");
    return 0;
}

static int print_bool(FILE *new_file, data_t *curr_row)
{
    if (curr_row->b_value)
        return fprintf(new_file, "%s", "true");
    else
        return fprintf(new_file, "%s", "false");
}

static int handle_type(FILE *new_file, data_t *row, int i)
{
    switch (row[i].data_type) {
        case STRING:
            return fprintf(new_file, "%s", row[i].c_value);
        case FLOAT:
            return fprintf(new_file, "%f", row[i].f_value);
        case UINT:
            return fprintf(new_file, "%u", row[i].ui_value);
        case INT:
            return fprintf(new_file, "%d", row[i].i_value);
        case BOOL:
            return print_bool(new_file, &(row[i]));
        case UNDEFINED:
            return -1;
    }
}

static int print_data(data_t *row, FILE *new_file, int nb_columns,
    const char *sep)
{
    int is_error = 0;

    for (int i = 0; i < nb_columns; i++) {
        is_error = handle_type(new_file, row, i);
        if (i != nb_columns - 1)
            is_error = fprintf(new_file, "%s", sep);
        if (is_error < 0)
            return 1;
    }
    return 0;
}

int write_data(dataframe_t *df, FILE *new_file)
{
    for (size_t i = 0; i < df->data->count; i++) {
        if (print_data(df->data->rows[i], new_file, df->nb_columns,
                df->separator))
            return 1;
        if (i != df->data->count - 1)
            fprintf(new_file, "\n");
        else
            continue;
    }
    return 0;
}

int check_filename(const char *filename)
{
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == '/')
            return 1;
    }
    return 0;
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *new_file = NULL;

    if (check_filename(filename)) {
        dprintf(2, "Invalid file name\n");
        return 84;
    } else
        new_file = fopen(filename, "w+");
    if (new_file == NULL) {
        perror("fopen");
        return 84;
    } else {
        if (write_header(dataframe, new_file))
            return 84;
        if (write_data(dataframe, new_file))
            return 84;
        fclose(new_file);
        return 0;
    }
}
