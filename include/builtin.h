/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** builtins
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #define NB_BUILTIN 8

typedef struct builtins_args_s {
    data_t *data;
    char **envp;
    char **args;
} args_t;

typedef struct {
    const char *builtin_name;
    int (*builtin)(args_t *);
} builtins_t;

int exitsh(args_t *args);
int env(args_t *args);
int change_dir(args_t *args);
int set_env(args_t *args);
int unset_env(args_t *args);
int which(args_t *args);
int where(args_t *args);
int set(args_t *args);

static const builtins_t bt_array[] = {{"exit", &exitsh}, {"env", &env},
    {"cd", &change_dir}, {"setenv", &set_env}, {"unsetenv", &unset_env},
    {"which", &which}, {"where", &where}, {"set", &set}};

#endif /* !BUILTIN_H_ */
