/*
** EPITECH PROJECT, 2026
** my_llm
** File description:
** train.c
*/

#include "my.h"

bool train(model_t *model, int iteration)
{
    bool has_error = false;
    float rate = 0.001;
    matrix_t Y_target = create_matrix(2, 1);
    fill_matrix(&Y_target, 0, 0, Y_TARGET_ONE);
    fill_matrix(&Y_target, 1, 0, Y_TARGET_TWO);
    matrix_t X = create_matrix(2, 1);
    fill_matrix(&X, 0, 0, 2.0);
    fill_matrix(&X, 1, 0, 3.0);
    matrix_t W1 = create_matrix(3, 2);
    fill_matrix(&W1, 0, 0, 1);
    fill_matrix(&W1, 0, 1, 5);
    fill_matrix(&W1, 1, 0, -3);
    fill_matrix(&W1, 1, 1, 2);
    fill_matrix(&W1, 2, 0, 1);
    fill_matrix(&W1, 2, 1, -4);
    matrix_t B1 = create_matrix(3, 1);
    fill_matrix(&B1, 0, 0, 1);
    fill_matrix(&B1, 1, 0, -3);
    fill_matrix(&B1, 2, 0, 1);
    printf("\n");
    matrix_t W2 = create_matrix(2, 3);
    fill_matrix(&W2, 0, 0, 1);
    fill_matrix(&W2, 0, 1, 5);
    fill_matrix(&W2, 0, 2, -3);
    fill_matrix(&W2, 1, 0, 2);
    fill_matrix(&W2, 1, 1, 1);
    fill_matrix(&W2, 1, 2, -4);
    matrix_t B2 = create_matrix(2, 1);
    fill_matrix(&B2, 0, 0, 2.0);
    fill_matrix(&B2, 1, 0, 3.0);
    for (int try = 0; try < iteration; try++) {
        matrix_t H = multiply_matrix_vector(W1, X);
        add_vectors(&H, B1);
        apply_relu(H);
        matrix_t Y_pred = multiply_matrix_vector(W2, H);
        add_vectors(&Y_pred, B2);
        apply_relu(Y_pred);
        matrix_t dY = create_matrix(2, 1);
        for (int i = 0; i < dY.line; i++) {
            if (Y_pred.data[i] <= 0) {
                dY.data[i] = 0;
                continue;
            }
            dY.data[i] = 2.0 * (Y_pred.data[i] - Y_target.data[i]);
        }
        matrix_t dW2 = compute_gradient_matrix(dY, H, W2.line, W2.column);
        matrix_t W2_T = transpose_matrix(W2);
        matrix_t dH = multiply_matrix_vector(W2_T, dY);
        for (int i = 0; i < dH.line; i++) {
            if (H.data[i] <= 0)
                dH.data[i] = 0;
        }
        matrix_t dW1 = compute_gradient_matrix(dH, X, W1.line, W1.column);
        update_weights(&W2, dW2, rate);
        update_weights(&W1, dW1, rate);
        update_weights(&B2, dY, rate);
        update_weights(&B1, dH, rate);
        model->layers[0] = W1;
        model->layers[1] = B1;
        model->layers[2] = W2;
        model->layers[3] = B2;
        if (!save_model(*model, "cerveau.bin"))
            has_error = true;
        print_matrix(Y_pred);
        free(H.data);
        free(Y_pred.data);
        free(dY.data);
        free(dW2.data);
        free(W2_T.data);
        free(dH.data);
        free(dW1.data);
    }
    if (has_error)
        return false;
    return true;
}
