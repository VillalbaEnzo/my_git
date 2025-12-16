/*
** EPITECH PROJECT, 2025
** G-MUL-100-LYN-1-1-myradar-31
** File description:
** collision.c
*/

#include "../../include/my.h"

static bool is_in_tower_area(sprite_list_t *plane, sprite_list_t *all_entities)
{
    sprite_list_t *tmp = all_entities;
    sfFloatRect plane_bounds = sfRectangleShape_getGlobalBounds(plane->hitbox);
    sfVector2f plane_center = {
        plane_bounds.left + plane_bounds.width / 2.0f,
        plane_bounds.top + plane_bounds.height / 2.0f
    };

    while (tmp) {
        // On cherche seulement les TOURS
        if (!tmp->is_plane) {
            sfVector2f tower_pos = tmp->start_pos; // Les tours ne bougent pas
            float radius = (float)tmp->radius;
            
            // Calcul de distance (Pythagore)
            float dx = plane_center.x - tower_pos.x;
            float dy = plane_center.y - tower_pos.y;
            
            // Si la distance est inférieure au rayon, on est protégé
            if ((dx * dx + dy * dy) <= (radius * radius))
                return true;
        }
        tmp = tmp->next;
    }
    return false;
}

static void check_collision_for_entity(game_t *game, quadtree_t *qt, sprite_list_t *plane)
{
    sprite_list_t *nearby[1024]; // Buffer pour les voisins
    int count = 0;
    sfFloatRect area = sfRectangleShape_getGlobalBounds(plane->hitbox);
    
    // 1. Récupération optimisée des voisins
    get_planes_in_area(qt, area, nearby, &count);

    // 2. Vérification précise
    for (int i = 0; i < count; i++) {
        sprite_list_t *other = nearby[i];

        // Conditions : Pas soi-même, c'est un avion, en vol, pas détruit
        if (plane != other && other->is_plane && other->has_taken_off && 
            !other->has_arrived && !other->is_destroyed) {
            
            sfFloatRect other_box = sfRectangleShape_getGlobalBounds(other->hitbox);
            
            if (sfFloatRect_intersects(&area, &other_box, NULL)) {
                // COLLISION CONFIRMÉE -> DESTRUCTION
                plane->is_destroyed = true;
                other->is_destroyed = true;
            }
        }
    }
}

void check_collisions(game_t *game)
{
    sfFloatRect screen = {0, 0, 1920, 1080};
    quadtree_t *qt = create_quadtree(screen);
    sprite_list_t *tmp = game->entities;

    // 1. Remplissage du Quadtree
    while (tmp) {
        if (tmp->is_plane && tmp->has_taken_off && !tmp->has_arrived && !tmp->is_destroyed) {
            insert(qt, tmp);
        }
        tmp = tmp->next;
    }

    // 2. Vérification des collisions
    tmp = game->entities;
    while (tmp) {
        if (tmp->is_plane && tmp->has_taken_off && !tmp->has_arrived && !tmp->is_destroyed) {
            // Si l'avion n'est PAS sous une tour, on vérifie les collisions
            if (!is_in_tower_area(tmp, game->entities)) {
                check_collision_for_entity(game, qt, tmp);
            }
        }
        tmp = tmp->next;
    }

    // 3. Nettoyage
    destroy_quadtree(qt);
}