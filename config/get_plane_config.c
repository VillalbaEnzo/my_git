/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31 [WSL: Ubuntu-24.04]
** File description:
** get_plane_config.c
*/

#include "../include/my.h"

static void add_entity(game_t *game, sprite_list_t *node)
{
    node->next = game->entities;
    game->entities = node;
}

static bool parse_plane(game_t *game, char **arr)
{
    sprite_list_t *node = malloc(sizeof(sprite_list_t));

    if (!node || !arr[1] || !is_nbr(arr[1]) || !arr[2] || !is_nbr(arr[2])
        || !arr[3] || !is_nbr(arr[3]) || !arr[4] || !is_nbr(arr[4]) || !arr[5]
        || !is_nbr(arr[5]) || !arr[6] || !is_nbr(arr[6])) {
        free_array(arr);
        free(node);
        return false;
    }
    init_sprite_list(node);
    node->is_plane = true;
    node->start_pos = (sfVector2f){my_getnbr(arr[1]), my_getnbr(arr[2])};
    node->end_pos = (sfVector2f){my_getnbr(arr[3]), my_getnbr(arr[4])};
    node->speed = my_getnbr(arr[5]);
    node->delay = (int)my_getnbr(arr[6]);
    node->current_pos = node->start_pos;
    node->has_taken_off = false;
    node->has_arrived = false;
    add_entity(game, node);
    return true;
}

static bool parse_tower(game_t *game, char **arr)
{
    sprite_list_t *node = malloc(sizeof(sprite_list_t));

    if (!node || !arr[1] || !is_nbr(arr[1]) || !arr[2] || !is_nbr(arr[2]) ||
        !arr[3] || !is_nbr(arr[3])) {
        free_array(arr);
        free(node);
        return false;
    }
    init_sprite_list(node);
    node->is_plane = false;
    node->start_pos = (sfVector2f){my_getnbr(arr[1]), my_getnbr(arr[2])};
    node->radius = my_getnbr(arr[3]);
    add_entity(game, node);
    return true;
}

static bool check_err(char *line, FILE *file, char **arr)
{
    free_array(arr);
    free(line);
    fclose(file);
    return false;
}

bool get_start_coord(game_t *game, const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    char **arr = NULL;
    size_t len = 0;

    if (!file)
        return false;
    while (getline(&line, &len, file) != -1) {
        arr = my_str_to_word_array(line);
        if (!arr || !arr[0])
            return check_err(line, file, arr);
        if ((arr[0][0] == 'A' && !parse_plane(game, arr)) || (arr[0][0] == 'T'
                && !parse_tower(game, arr)))
            return check_err(line, file, arr);
        free_array(arr);
    }
    free(line);
    fclose(file);
    return true;
}
