/*
** EPITECH PROJECT, 2025
** asm
** File description:
** Header for the operations
*/

#ifndef OP_H_
    #define OP_H_

    #define _GNU_SOURCE

    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483648)

    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4 /* this may not be changed 2^*IND_SIZE */

    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"

    #define PACKED_ATTR __attribute__((packed))
/*
** regs
*/
    #define REG_NUMBER 16 /* r1 <--> rx */

/*
**
*/
typedef char args_type_t;

/* register */
    #define T_REG 1
/* direct  (ld  #1,r1  put 1 into r1) */
    #define T_DIR 2
/* indirect always relative (ld 1,r1 put what's in the address (1+pc) into r1
(4 bytes )) */
    #define T_IND 4
/* LABEL */
    #define T_LAB 8

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
} op_t;

/*
** size (in bytes)
*/
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

/*
** op_tab
*/
extern const op_t op_tab[];

/*
** header
*/
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct
header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    char padding[3];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
    char padding2[3];
} header_t;

/*
** data structure
*/

/* ARGS */

typedef struct arg_s {
    args_type_t type;
    int distance;
    char *label;
} arg_t;

/* LABEL */

typedef struct label_s {
    char *name;
    int pos;
    struct label_s *next;
} label_t;

/* INSTRUCTION */

typedef struct inst_s {
    int opcode;
    int coding_byte;
    arg_t args[MAX_ARGS_NUMBER];
    int pos;
    int total;
    struct inst_s *next;
} inst_t;

typedef struct data_s {
    header_t *header;
    char *filename;
    inst_t *inst;
    label_t *labels;
} data_t;

/*
** live
*/
    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

/* PARSING */

data_t *parse_file(const char *filename);
header_t *parse_header(FILE *fstream);
void parse_body(FILE *file, data_t *data);

/* ERROR HANDLING */

bool is_file_valid(const char *filename);

/* UTILS */

int my_strncmp(char const *s1, char const *s2, int n);
int my_strcmp(char const *s1, char const *s2);
char *read_line(FILE *fstream, char *line, bool stop_on_nl);
int my_strlen(char const *str);
void *my_memset(void *to_set, int c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char **str_to_token_array_delim(char *src, char delim);
void free_array(void **array);
void *close_and_ret_null(FILE *fstream);
void *free_return(void *to_free);
char *my_strcat(char *dest, char const *src);
char *get_final_name(const char *fn);
unsigned int swap_endian_int(unsigned int data);
unsigned short swap_endian_short(unsigned int data);
char *clean_line(char *line);
int my_getnbr(char const *str);

bool write_header(data_t *data);

#endif /* OP_H_ */
