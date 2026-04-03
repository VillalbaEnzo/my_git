/*
** EPITECH PROJECT, 2025
** G-CPE-200-LYN-2-1-robotfactory-5 [WSL: Ubuntu-24.04]
** File description:
** parse_label.c
*/

#include "op.h"

static char *extract_label(char **line_ptr)
{
    int i = 0;
    char *line = *line_ptr;
    char *label_name = NULL;

    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') {
        if (line[i] == LABEL_CHAR) { // LABEL_CHAR est ':'
            // On a trouvé un label ! On l'alloue et on le copie
            label_name = my_calloc(i + 1, sizeof(char));
            if (!label_name)
                return NULL;
            my_strncpy(label_name, line, i);
            
            // On avance le pointeur d'origine JUSTE APRÈS le ':'
            *line_ptr = line + i + 1;
            return label_name;
        }
        i++;
    }
    // Si on n'a pas trouvé de ':', ce n'est pas un label
    return NULL;
}