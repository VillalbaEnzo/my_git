#ifndef STRUCT_H
    #define STRUCT_H

/* MATRIX */
typedef struct {
    float *data;
    int line;
    int column;
} matrix_t;

typedef struct {
    int count;
    matrix_t *layers;
} model_t;

#endif