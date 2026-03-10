/*
** EPITECH PROJECT, 2026
** cuddle [WSL: Ubuntu]
** File description:
** database
*/

#ifndef DATABASE_H_
    #define DATABASE_H_

    #define _GNU_SOURCE

    #include <unistd.h>
    #include <stdbool.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    const char *name;
    column_type_t type;
} column_t;

typedef struct header_s {
    column_t *columns;
    size_t count;
    size_t capacity;
} header_t;

typedef struct {
    column_type_t data_type;
    union {
        char *c_value;
        int i_value;
        unsigned int ui_value;
        float f_value;
        bool b_value;
    };
} data_t;

typedef struct {
    data_t **rows;
    size_t count;
    size_t capacity;
} rows_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    header_t *header;
    rows_t *data;
    const char *separator;
} dataframe_t;

/* CORE */

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);

/* MY_UTILS */

int my_strcasecmp(char *s1, char *s2);
FILE *open_file(const char *filename);
header_t *init_header(void);
header_t *resize_header(header_t *header);
rows_t *init_rows(void);
rows_t *resize_rows(rows_t *data);
column_type_t set_column_type(char *token);
void *return_value(dataframe_t *dataframe, int row, int columns_idx);

/* UTILITIES*/

void df_free(dataframe_t *dataframe);
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);

/* BASIC */

dataframe_shape_t df_shape(dataframe_t *dataframe);

#endif /* !DATABASE_H_ */
