/*
** EPITECH PROJECT, 2026
** minishell1 [WSL: Ubuntu]
** File description:
** cmd_array
*/

#ifndef CMD_ARRAY_H_
    #define CMD_ARRAY_H_

    #include <unistd.h>

static const char *const def_paths[] = {"/usr/local/bin", "/usr/bsd",
    "/bin", "/usr/bin", ".", NULL};
static const char *const operators[] = {"<", ">", "<<", ">>", NULL};
static const char *const symbols[] = {";", "|", "&&", "||", NULL};

#endif /* !CMD_ARRAY_H_ */
