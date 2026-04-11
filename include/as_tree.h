/*
** EPITECH PROJECT, 2026
** cpsh
** File description:
** as_tree
*/

#ifndef AS_TREE_H_
    #define AS_TREE_H_

    #define PIPE_READ 0
    #define PIPE_WRITE 1
    #define MAX_PIPE 2

typedef enum {
    NONE,
    COMMAND,
    PIPE,
    AND,
    XOR,
    SEMI_COLON
} node_type_t;

typedef enum {
    SIMPLE_L,
    SIMPLE_R,
    DOUBLE_L,
    DOUBLE_R,
    NOT_R
} redir_type_t;

typedef struct redir_s {
    redir_type_t type;
    const char *filename;
    int save;
} redir_t;


typedef struct ast_command {
    char **arguments;
    redir_t *redirections;
    int redir_count;
} ast_cmd_t;

typedef struct ast_pipe {
    struct ast_node *writer;
    struct ast_node *reader;
} ast_pipe_t;

typedef struct ast_and {
    struct ast_node *cmd1;
    struct ast_node *cmd2;
} ast_and_t;

typedef struct ast_xor {
    struct ast_node *cmd1;
    struct ast_node *cmd2;
} ast_xor_t;

typedef struct ast_semicolon {
    struct ast_node *left;
    struct ast_node *right;
} ast_semic_t;

struct ast_node {
    node_type_t type;
    union {
        ast_cmd_t *cmd_node;
        ast_pipe_t *pipe_node;
        ast_semic_t *semic_node;
        ast_and_t *and_node;
        ast_xor_t *xor_node;
    };
};

struct ast_node *build_tree(char **token);

#endif /* !AS_TREE_H_ */
