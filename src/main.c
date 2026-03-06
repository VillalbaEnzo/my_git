/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** main.c
*/

#include "my.h"

static void print_help(void)
{
    printf("My World - A 3D Terrain Editor\n\n"
        "DESCRIPTION:\n"
        "    'My World' is an isometric world editor.\n"
        "    You can create and sculpt 3D landscapes in real-time using\n"
        "    various tools and brushes.\n\n"
        "AVAILABLE USER INPUTS:\n\n"
        "    [MOUSE LEFT CLICK]\n"
        "    - In Menus: Interact with 'Start', 'Load', and 'Quit' buttons.\n"
        "    - In Game: Use the current brush to modify the terrain.\n\n"
        "    [KEYBOARD]\n"
        "    - Arrow Keys: Move the camera view across the map.\n"
        "    - 'A' and 'D' Keys: Rotate the map to change the orientation.\n"
        "    - Text Input: Type in 'Radius' or 'Strength'"
        "boxes to adjust your brush.\n\n"
        "    [WINDOW]\n"
        "    - Close Button: Exit the application.\n"
        "    - Default Resolution: %dx%d.\n", GAME_WIDTH, GAME_HEIGHT);
}

int main(int argc, char **argv)
{
    game_t *game;

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }
    if (argc == 1) {
        game = create_game();
        if (!game)
            return 84;
        game_loop(game);
        destroy_game(game);
        return 0;
    }
    return 84;
}
