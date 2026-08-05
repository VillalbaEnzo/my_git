/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** struct.h
*/

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

/* TOKEN */
typedef struct vocab_node_s {
    int id;
    char *token;
    struct vocab_node_s *next;
} vocab_node_t;

typedef struct {
    char **tokens;
    int size;
} text_buffer_t;

#endif