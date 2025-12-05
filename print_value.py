##
## EPITECH PROJECT, 2025
## G-MAT-100-LYN-1-1-103cipher-14
## File description:
## print_value.py
##

def print_encrypt_matrix(matrix):
    print("Encrypted message:")
    temp = []
    for line in matrix:
        for col in line:
            temp.append(col)
    print(*temp)

def print_key_matrix(matrix):
    print("Key matrix:")
    for line in matrix:
        formatted_line = []
        for value in line:
            if isinstance(value, float):
                formatted_value = str(round(value, 3))
            else:
                formatted_value = str(value)
            formatted_line.append(formatted_value)
        print("\t".join(formatted_line))
    print()

def print_decrypted_message(matrix):
    print("Decrypted message:")
    for line in matrix:
        for i in line:
            if round(i) != 0:
                print(chr(round(i)), end='')
    print()

