/*
** EPITECH PROJECT, 2026
** init_levels.c
** File description:
** init_levels
*/

#include "wolf3d.h"

static char *get_next_data(FILE *fp, char **line, size_t *len)
{
    while (getline(line, len, fp) != -1) {
        if ((*line)[0] == '#' || (*line)[0] == '\n' || (*line)[0] == '\r')
            continue;
        (*line)[strcspn(*line, "#\r\n")] = '\0';
        return *line;
    }
    return NULL;
}

static int parse_grid(FILE *fp, level_t *level)
{
    char *line = NULL;
    char *ptr;
    size_t len = 0;

    level->map->grid = calloc(level->map->height, sizeof(int *));
    if (!level->map->grid)
        return (EXIT_FAILURE);
    for (int y = 0; y < level->map->height; y++) {
        level->map->grid[y] = calloc(level->map->witdh, sizeof(int));
        if (!level->map->grid[y] || !get_next_data(fp, &line, &len)) {
            free(line);
            return (EXIT_FAILURE);
        }
        ptr = line;
        for (int x = 0; x < level->map->witdh; x++)
            level->map->grid[y][x] = strtol(ptr, &ptr, 10);
    }
    free(line);
    return (EXIT_SUCCESS);
}

static int parse_file(level_t *level, char const *file)
{
    FILE *fp = fopen(file, "r");
    char *line = NULL;
    size_t len = 0;
    int retv;

    if (!fp)
        return (EXIT_FAILURE);
    if (get_next_data(fp, &line, &len))
        level->name = strdup(line);
    if (get_next_data(fp, &line, &len))
        sscanf(line, "%d %d", &level->map->witdh, &level->map->height);
    if (get_next_data(fp, &line, &len))
        sscanf(line, "%f %f", &level->spawnpos.x, &level->spawnpos.y);
    if (get_next_data(fp, &line, &len))
        sscanf(line, "%f %f", &level->spawndir.x, &level->spawndir.y);
    retv = parse_grid(fp, level);
    free(line);
    fclose(fp);
    return (retv);
}

static level_t *get_level(char const *file)
{
    level_t *level = calloc(1, sizeof(level_t));

    if (!level)
        return (NULL);
    level->map = calloc(1, sizeof(map_t));
    if (!level->map || parse_file(level, file) == EXIT_FAILURE) {
        free_level(level);
        return (NULL);
    }
    return (level);
}

level_t **init_levels(void)
{
    char *mapfiles[] = {LEVEL0_FILE, NULL};
    level_t **levels = malloc(sizeof(level_t *) * (NBR_LEVEL + 1));

    if (!levels)
        return (NULL);
    for (int i = 0; mapfiles[i]; i++) {
        levels[i] = get_level(mapfiles[i]);
        if (!levels[i]) {
            free_levels(levels);
            return (NULL);
        }
    }
    levels[NBR_LEVEL] = NULL;
    return (levels);
}
