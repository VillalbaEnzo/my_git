/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** read_csv
*/

#include "database.h"

static char *read_line(FILE *stream)
{
    ssize_t bytes_read = 0;
    size_t thrash = 0;
    char *buffer = NULL;

    bytes_read = getline(&buffer, &thrash, stream);
    if (bytes_read == -1) {
        perror("getline");
        return NULL;
    } else {
        buffer[bytes_read - 1] = '\0';
        return buffer;
    }
}

static int append_column(header_t *header, char *token)
{
    if (header->count >= header->capacity)
        header = resize_header(header);
    if (header->columns == NULL)
        return 1;
    header->columns[header->count] = (column_t){strdup(token), UNDEFINED};
    header->count++;
    return 0;
}

static bool is_true(char *token)
{
    if (!my_strcasecmp(token, "true"))
        return true;
    else
        return false;
}

static void set_union_value(data_t *row, char *token)
{
    switch (row->data_type) {
        case STRING:
            row->c_value = strdup(token);
            return;
        case FLOAT:
            row->f_value = strtof(token, NULL);
            return;
        case INT:
            row->i_value = atoi(token);
            return;
        case UINT:
            row->ui_value = (unsigned int)atoi(token);
        case BOOL:
            row->b_value = is_true(token);
            return;
        case UNDEFINED:
            return;
    }
}

data_t *append_and_set_type(char *f_line, const char *seperator,
    dataframe_t *df)
{
    data_t *row = malloc(sizeof(data_t) * df->nb_columns);
    char *token = strtok(f_line, seperator);

    if (row == NULL || token == NULL)
        return NULL;
    for (int i = 0; i < df->nb_columns; i++) {
        df->header->columns[i].type = set_column_type(token);
        row[i].data_type = df->header->columns[i].type;
        set_union_value(&(row[i]), token);
        token = strtok(NULL, seperator);
    }
    free(f_line);
    f_line = NULL;
    return row;
}

data_t *append_row(char *line, const char *sep, dataframe_t *df, rows_t *data)
{
    data_t *row = malloc(sizeof(data_t) * df->nb_columns);
    char *token = strtok(line, sep);

    if (data->count >= data->capacity)
        data = resize_rows(data);
    if (data == NULL)
        return NULL;
    if (row == NULL || token == NULL)
        return NULL;
    for (int i = 0; i < df->nb_columns; i++) {
        row[i].data_type = df->header->columns[i].type;
        set_union_value(&(row[i]), token);
        token = strtok(NULL, sep);
    }
    return row;
}

header_t *read_header(FILE *stream, const char *separator)
{
    char *line = read_line(stream);
    header_t *header = init_header();
    char *token = NULL;

    if (line == NULL || header == NULL)
        return NULL;
    token = strtok(line, separator);
    while (token != NULL) {
        if (append_column(header, token))
            return NULL;
        token = strtok(NULL, separator);
    }
    free(line);
    return header;
}

rows_t *read_data(FILE *stream, const char *seperator, dataframe_t *df)
{
    rows_t *data = init_rows();
    char *line = read_line(stream);

    if (data == NULL)
        return NULL;
    data->rows[data->count] = append_and_set_type(line, seperator, df);
    if (data->rows[data->count] == NULL)
        return NULL;
    data->count++;
    line = read_line(stream);
    while (line != NULL) {
        data->rows[data->count] = append_row(line, seperator, df, data);
        if (data->rows[data->count] == NULL)
            return NULL;
        data->count++;
        free(line);
        line = read_line(stream);
    }
    return data;
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *stream = open_file(filename);
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (stream == NULL || df == NULL)
        return NULL;
    if (separator == NULL)
        df->separator = ",";
    else
        df->separator = separator;
    df->nb_columns = 0;
    df->nb_rows = 0;
    df->header = read_header(stream, df->separator);
    if (df->header == NULL)
        return NULL;
    df->nb_columns = df->header->count;
    df->data = read_data(stream, df->separator, df);
    df->nb_rows = df->data->count;
    fclose(stream);
    return df;
}
