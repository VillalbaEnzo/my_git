/*
** EPITECH PROJECT, 2025
** G-ING-200-LYN-2-1-myworld-1 [WSL: Ubuntu-24.04]
** File description:
** handle_map_click.c
*/

#include "my.h"

static sfVector2i get_mouse_map_pos(game_t *game, sfVector2i mouse_pos)
{
    sfVector2i map_pos = {-1, -1};
    float min_dist = -1.0f;

    // On parcourt tous les points de la carte
    for (int y = 0; y < game->map->height; y++) {
        for (int x = 0; x < game->map->width; x++) {
            
            // On récupère la position 2D du point actuel sur l'écran
            sfVector2f p = game->map->points_2d[y][x];
            
            // On calcule la distance (au carré) entre la souris et le point
            float dx = p.x - mouse_pos.x;
            float dy = p.y - mouse_pos.y;
            float dist = (dx * dx) + (dy * dy); // Pas besoin de sqrt, c'est plus optimisé

            // Si c'est le premier point ou qu'il est plus proche que l'ancien
            if (min_dist == -1.0f || dist < min_dist) {
                min_dist = dist;
                map_pos.x = x;
                map_pos.y = y;
            }
        }
    }
    
    return map_pos;
}

void handle_map_click(game_t *game)
{
    // On vérifie que le clic gauche est maintenu enfoncé
    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;

    // Optionnel mais recommandé : 
    // Vérifier ici qu'on ne clique pas sur l'interface (la barre d'outil, les TextBox, etc.)
    // Si la souris est sur l'UI, on fait un "return;" pour ne pas modifier la map en dessous.

    // 1. Récupérer la position de la souris sur l'écran
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);

    // 2. Convertir cette position écran en coordonnées (X, Y) sur ton tableau z_map
    // (Tu dois utiliser la formule inverse de ta projection isométrique ici)
    sfVector2i map_pos = get_mouse_map_pos(game, mouse_pos);

    // 3. Si le clic est bien à l'intérieur des limites de la carte
    if (map_pos.x >= 0 && map_pos.x < game->map->width &&
        map_pos.y >= 0 && map_pos.y < game->map->height) {
        
        // 4. On appelle le brush sur la case ciblée !
        apply_brush(game, map_pos.x, map_pos.y);
    }
}