/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** mysh include header
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #define _GNU_SOURCE

    #include <unistd.h>
    #include <stdio.h>
    #include <limits.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <dirent.h>
    #include <stdbool.h>
    #include <glob.h>
    #include <fnmatch.h>
    #include "as_tree.h"

    #define CMD cmd_node->arguments[0]
    #define DEF_EXIT_SIG 128

typedef struct local_var_s {
    char *name;
    char *value;
    struct local_var_s *next;
} local_var_t;

typedef struct alias_s {
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

typedef struct {
    char **tokens;
    char **envp;
    struct ast_node *root;
    local_var_t *local_vars;
    alias_t *aliases;
} data_t;

void display_prompt(void);

/* INITS */

data_t *init_data(char **envp);

/* COMMAND EXECUTION*/

int traverse_tree(struct ast_node *root, data_t *data, char **envp);
char *handle_path(char *command, char **envp, char *command_saver);
int execute_command(ast_cmd_t *cmd_node, char **envp, data_t *data);
int exec_pipe(ast_pipe_t *p_node, data_t *data);
int exec_builtin(ast_cmd_t *cmd_node, char **envp, data_t *data);
int child_code(ast_cmd_t *cmd_node, char **envp);
int exec_and(struct ast_node *root, data_t *data, char **envp);
int exec_or(struct ast_node *root, data_t *data, char **envp);
int exec_if(struct ast_node *node, data_t *data, char **envp);

/* INPUT PARSING */

char *read_input(data_t *data, int ret_value, int is_term);

/* GLOBBING */

char **glob_arg(char **args);
int args_exp(ast_cmd_t *cmd_node, data_t *data);
char *var_substitution(char *to_sub, data_t *data);
char **quote_removal(char **args);
char *expand_cmd(char **cmd_tokens, data_t *data);
char *command_sub(char *token, data_t *data);

/* PATH HANDLING */

int find_path(char **envp);
char *skip_env_name(char *path);

/* AST BUILDING */

struct ast_node *get_command(char **token, int *last_pos);
struct ast_node *create_pipe(struct ast_node *root, char **token,
    int *last_pos);
struct ast_node *create_semi_colon(struct ast_node *prev_root,
    char **token, int *last_pos);
struct ast_node *create_and_node(struct ast_node *root, char **token,
    int *last_pos);
struct ast_node *create_or_node(struct ast_node *root, char **token,
    int *last_pos);
struct ast_node *create_if_node(char **token, int *last_pos);

/* SIGNALS */

int handle_sig(int c_status);

/* REDIRECTIONS */

void swap_fd(redir_t *redir_array, int redir_count);
void reset_fds(redir_t *redir_array, int redir_count);

/* ERROR HANDLING */

bool check_pipe(struct ast_node *root);
bool pre_check_tree(struct ast_node *root, bool is_first_node,
    node_type_t prev_node_type);

/* ALIASES */

void expand_aliases(ast_cmd_t *cmd, data_t *data);

/* VARIABLE */

local_var_t *add_local_var(local_var_t *head, char *name, char *value);

/* FREE */

void free_array(void **array);
void free_pipe(ast_pipe_t *pipe_node);
void free_semi_colon(ast_semic_t *semic_node);
void free_and(ast_and_t *and_node);
void free_or(ast_or_t *or_node);
void free_from_root(struct ast_node *root);
void free_data(data_t *data);
void free_if(ast_if_t *if_node);

#endif /* !MYSH_H_ */
