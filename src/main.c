/*
** EPITECH PROJECT, 2026
** robotfactory
** File description:
** main
*/
#include "op.h"

static void debug_print_data(data_t *data)
{
    label_t *tmp_lbl = data->labels;
    inst_t *tmp_inst = data->inst;

    printf("=== AFFICHAGE DES LABELS ===\n");
    while (tmp_lbl) {
        printf("Label trouve : [%s]\n", tmp_lbl->name);
        tmp_lbl = tmp_lbl->next;
    }

    printf("\n=== AFFICHAGE DES INSTRUCTIONS ===\n");
    while (tmp_inst) {
        printf("Opcode : %d | Coding Byte : %d\n", tmp_inst->opcode, tmp_inst->coding_byte);
        
        // Affichage des arguments de l'instruction
        for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
            if (tmp_inst->args[i].type == 0) // S'il n'y a pas d'argument à cette position
                continue;
            
            printf("  -> Arg %d : Type=%d | ", i + 1, tmp_inst->args[i].type);
            if (tmp_inst->args[i].label)
                printf("Label=%%:%s\n", tmp_inst->args[i].label);
            else
                printf("Valeur=%d\n", tmp_inst->args[i].distance);
        }
        printf("------------------------------------\n");
        tmp_inst = tmp_inst->next;
    }
}

int main(int ac, char **av)
{
    data_t *to_write = NULL;

    if (ac != 2 || is_file_valid(av[1]) == false)
        return 84;
    to_write = parse_file(av[1]);
    if (!to_write || !to_write->header)
        return 84;
    debug_print_data(to_write);
    write_header(to_write);
    return 84;
}
