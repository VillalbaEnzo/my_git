/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_body.c
*/

#include "op.h"

static void clear_com(char *line)
{
    int idx = 0;

    if (!line)
        return;
    while (line[idx] != '\0' && line[idx] != COMMENT_CHAR)
        idx++;
    if (line[idx] == COMMENT_CHAR)
        line[idx] = '\0';
}

static inst_t *find_inst(char *line)
{
    int idx = 0;
    char *word = NULL;
    inst_t *temp = NULL;

    while (line[idx] != ' ' && line[idx] != '\t' && line[idx] != '\0')
        idx++;
    if (idx == 0)
        return NULL;
    word = my_calloc(idx + 1, sizeof(char));
    if (!word)
        return NULL;
    word = my_strncpy(word, line, idx);
    word[idx] = '\0';
    printf("mot: %s\n", word);
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (my_strcmp(op_tab[i].mnemonique, word) == 0) {
            temp = my_calloc(1, sizeof(inst_t));
            temp->opcode = op_tab[i].code;
        }
    }
    free(word);
}

void parse_body(FILE *file)
{
    int counter = 0;
    inst_t *inst = NULL;
    label_t *label = NULL;
    char *line = NULL;

    line = read_line(file, line, false);
    while (line) {
        clear_com(line);
        if (line[0] != '\0') {
            inst = find_inst(clean_line(line));
            printf("%s\n", line);
        }
        free(line);
        line = read_line(file, line, false);
    }
}
