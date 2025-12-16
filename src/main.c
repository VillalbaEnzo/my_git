/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "../include/my.h"

static void print_help(void)
{
    mini_printf("Air traffic simulation panel\n"
        "USAGE\n"
        "    ./my_radar [OPTIONS] path_to_script\n"
        "    path_to_script\tThe path to the script file.\n"
        "OPTIONS\n"
        "    -h\tprint the usage and quit.\n"
        "USER INTERACTIONS\n"
        "    - 'L' key\tenable/disable hitboxes and areas.\n"
        "    - 'S' key\tenable/disable sprites.\n");
}

int main(int argc, char **argv)
{
    game_t *game;

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }
    if (argc != 2)
        return 84;
    game = create_game();
    if (!game)
        return 84;
    if (!get_start_coord(game, argv[1])) {
        destroy_game(game);
        return 84;
    }
    load_entities_resources(game);
    game_loop(game);
    destroy_game(game);
    return 0;
}
