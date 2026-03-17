/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** describe
*/

#include "dataframe.h"

static void print_stats(const char *name, describe_t *stats)
{
    printf("Column: %s\n", name);
    printf("Count: %i\n", stats->count);
    printf("Mean: %.2f\n", stats->mean);
    printf("Std: %.2f\n", stats->std_dev);
    printf("Min: %.2f\n", stats->min);
    printf("Max: %.2f\n", stats->max);
    free(stats);
}

static double calc_mean(double *values, int count)
{
    double sum = 0;

    for (int i = 0; i < count; i++)
        sum += values[i];
    return sum / (double)count;
}

static double calc_std_dev(double *values, int count, double mean)
{
    double *dev = calloc(count, sizeof(double));
    double dev_mean = 0;

    if (!dev)
        return 0;
    for (int i = 0; i < count; i++)
        dev[i] = pow((values[i] - mean), 2);
    dev_mean = calc_mean(dev, count);
    free(dev);
    return sqrt(dev_mean);
}

static void calc_stats(describe_t *stats, double *values)
{
    stats->mean = calc_mean(values, stats->count);
    stats->std_dev = calc_std_dev(values, stats->count, stats->mean);
    free(values);
}

void get_int_stats(describe_t *stats, double *values, int pos, dataframe_t *df)
{
    stats->count = df->nb_rows;
    stats->min = df->data->rows[0][pos].i_value;
    stats->max = df->data->rows[0][pos].i_value;
    for (int i = 0; i < df->nb_rows; i++) {
        values[i] = df->data->rows[i][pos].i_value;
        if (stats->min > df->data->rows[i][pos].i_value)
            stats->min = df->data->rows[i][pos].i_value;
        if (stats->max < df->data->rows[i][pos].i_value)
            stats->max = df->data->rows[i][pos].i_value;
    }
}

void get_uint_stats(describe_t *stats, double *values,
    int pos, dataframe_t *df)
{
    stats->count = df->nb_rows;
    stats->min = df->data->rows[0][pos].ui_value;
    stats->max = df->data->rows[0][pos].ui_value;
    for (int i = 0; i < df->nb_rows; i++) {
        values[i] = df->data->rows[i][pos].ui_value;
        if (stats->min > df->data->rows[i][pos].ui_value)
            stats->min = df->data->rows[i][pos].ui_value;
        if (stats->max < df->data->rows[i][pos].ui_value)
            stats->max = df->data->rows[i][pos].ui_value;
    }
}

void get_float_stats(describe_t *stats, double *values,
    int pos, dataframe_t *df)
{
    stats->count = df->nb_rows;
    stats->min = df->data->rows[0][pos].f_value;
    stats->max = df->data->rows[0][pos].f_value;
    for (int i = 0; i < df->nb_rows; i++) {
        values[i] = df->data->rows[i][pos].f_value;
        if (stats->min > df->data->rows[i][pos].f_value)
            stats->min = df->data->rows[i][pos].f_value;
        if (stats->max < df->data->rows[i][pos].f_value)
            stats->max = df->data->rows[i][pos].f_value;
    }
}

void describe_column(dataframe_t *df, int pos, column_type_t type)
{
    describe_t *stats = calloc(1, sizeof(describe_t));
    double *values = calloc(df->nb_rows, sizeof(double));

    if (!stats || !values)
        return;
    if (type == INT)
        get_int_stats(stats, values, pos, df);
    if (type == UINT)
        get_uint_stats(stats, values, pos, df);
    if (type == FLOAT)
        get_float_stats(stats, values, pos, df);
    calc_stats(stats, values);
    print_stats(df->header->columns[pos].name, stats);
}

void df_describe(dataframe_t *dataframe)
{
    if (!dataframe)
        return;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        switch (dataframe->header->columns[i].type) {
            case BOOL:
            case STRING:
            case UNDEFINED:
                continue;
            case INT:
                describe_column(dataframe, i, INT);
                continue;
            case UINT:
                describe_column(dataframe, i, UINT);
                continue;
            case FLOAT:
                describe_column(dataframe, i, FLOAT);
                continue;
        }
    }
}
