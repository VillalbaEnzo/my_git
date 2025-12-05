##
## EPITECH PROJECT, 2025
## G-MAT-100-LYN-1-1-103cipher-14 [WSL: Ubuntu-24.04]
## File description:
## matrix_op.py
##

import sys, math
from print_value import *

def get_ascii_matrix(string, size=-1):
    result = []
    idx = 0
    length = len(string)

    if size == -1:
        size = math.ceil(math.sqrt(length))
        nb_lines = size
    else:
        nb_lines = math.ceil(length / size)

    for _ in range(nb_lines):
        line = []
        for _ in range(size):
            if idx < length:
                line.append(ord(string[idx]))
                idx += 1
            else:
                line.append(0)
        result.append(line)
    return result

def multiply_matrices(matrix_one, matrix_two):
    line_a = len(matrix_one)
    if line_a == 0:
        return []
    cols_a = len(matrix_one[0])
    line_b = len(matrix_two)
    cols_b = len(matrix_two[0])

    if cols_a != line_b:
        return None
    result = []
    for _ in range(line_a):
        result.append([0] * cols_b)
    for i in range(line_a):
        for j in range(cols_b):
            temp = 0.0
            for k in range(cols_a):
                temp += matrix_one[i][k] * matrix_two[k][j]
            result[i][j] = int(round(temp))
    return result

def invert_matrix(matrix):
    n = len(matrix)
    augmented = []
    for i in range(n):
        identity_line = [0.0] * n
        identity_line[i] = 1.0
        augmented.append(matrix[i].copy() + identity_line)
    for i in range(n):
        pivot = augmented[i][i]
        if pivot == 0:
            for k in range(i + 1, n):
                if augmented[k][i] != 0:
                    augmented[i], augmented[k] = augmented[k], augmented[i]
                    pivot = augmented[i][i]
                    break
            else:
                sys.exit(84)
        for j in range(2 * n):
            augmented[i][j] = augmented[i][j] / pivot
        for k in range(n):
            if k != i:
                factor = augmented[k][i]
                for j in range(2 * n):
                    augmented[k][j] -= factor * augmented[i][j]
    inverse = []
    for i in range(n):
        inverse.append(augmented[i][n:])
    return inverse

def get_encrypted_matrix(message, cols):
    matrix = []
    current_line = []
    values = []
    for x in message.split():
        values.append(float(x))
    for val in values:
        current_line.append(val)
        if len(current_line) == cols:
            matrix.append(current_line)
            current_line = []
    if current_line:
        while len(current_line) < cols:
            current_line.append(0.0)
        matrix.append(current_line)
    return matrix

def encrypt(message, key_str):
    key_matrix = get_ascii_matrix(key_str)
    key_size = len(key_matrix)
    message_matrix = get_ascii_matrix(message, key_size)
    encrypt_matrix = multiply_matrices(message_matrix, key_matrix)
    print_key_matrix(key_matrix)
    print_encrypt_matrix(encrypt_matrix)

def decrypt(encrypted_message, key_str):
    key_matrix = get_ascii_matrix(key_str)
    inverted_key = invert_matrix(key_matrix)
    cols = len(key_matrix)
    encrypted_matrix = get_encrypted_matrix(encrypted_message, cols)
    result = multiply_matrices(encrypted_matrix, inverted_key)
    print_key_matrix(inverted_key)
    print_decrypted_message(result)