/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_instruction.c
*/

#include "op.h"

static inst_t *find_inst(char *line)
{
    int len = 0;
    inst_t *temp = NULL;

    while (line[len] != ' ' && line[len] != '\t' && line[len] != '\0')
        len++;
    if (len == 0)
        return NULL;
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (my_strncmp(op_tab[i].mnemonique, line, len) != 0 ||
            op_tab[i].mnemonique[len] != '\0')
            continue;
        temp = my_calloc(1, sizeof(inst_t));
        if (temp)
            temp->opcode = op_tab[i].code;
        break;
    }
    return temp;
}

inst_t *parse_instruction(char *line)
{
    inst_t *inst = NULL;
    int word_len = 0;

    if (line[0] == '\0')
        return NULL;
    inst = find_inst(line);
    if (!inst)
        return NULL;
    while (line[word_len] != ' ' && line[word_len] != '\t' &&
        line[word_len] != '\0') {
        word_len++;
    }
    line = clean_line(line + word_len);
    if (!parse_args(line, inst)) {
        free(inst);
        return NULL;
    }
    return inst;
}
