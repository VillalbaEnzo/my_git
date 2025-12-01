// #include <stdio.h>
// #include <stdlib.h> // Nécessaire pour malloc et free

// // 1. Définition de la structure du Noeud
// typedef struct Noeud {
//     int valeur;
//     struct Noeud* suivant;
// } Noeud;

// // --- FONCTIONS UTILITAIRES ---
// void libererListe(Noeud* tete) {
//     Noeud* temp;
    
//     while (tete != NULL) {
//         temp = tete;        // On garde une référence sur le noeud actuel
//         tete = tete->suivant; // On avance la tête vers le suivant D'ABORD
//         free(temp);         // Maintenant on peut supprimer l'ancien noeud
//     }
// }
// // Fonction pour créer un nouveau noeud (allocation mémoire)
// Noeud* creerNoeud(int data) {
//     // On demande à l'ordinateur de la place en mémoire
//     Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud)); 
//     if (nouveau == NULL) {
//         printf("Erreur d'allocation mémoire\n");
//         exit(1);
//     }
//     nouveau->valeur = data;
//     nouveau->suivant = NULL;
//     return nouveau;
// }

// // Fonction pour afficher la liste
// void afficherListe(Noeud* tete) {
//     Noeud* temp = tete;
//     while (temp != NULL) {
//         printf("%d -> ", temp->valeur);
//         temp = temp->suivant;
//     }
//     printf("NULL\n");
// }

// // --- LES FONCTIONS DEMANDÉES ---

// // A. AJOUTER (au début, pour simplifier la construction)
// // On utilise Noeud** (pointeur de pointeur) car on modifie la tête de liste
// void ajouterDebut(Noeud** tete_ref, int data) {
//     Noeud* nouveau = creerNoeud(data);
//     nouveau->suivant = *tete_ref; // Le nouveau pointe vers l'ancienne tête
//     *tete_ref = nouveau;          // La tête devient le nouveau noeud
// }

// // B. INSÉRER ENTRE DEUX (Après un noeud spécifique)
// void insererApres(Noeud* noeud_precedent, int data) {
//     if (noeud_precedent == NULL) {
//         printf("Le noeud précédent ne peut pas être NULL\n");
//         return;
//     }
    
//     // 1. Créer le nouveau noeud
//     Noeud* nouveau = creerNoeud(data);
    
//     // 2. Le nouveau pointe vers ce que pointait le précédent
//     nouveau->suivant = noeud_precedent->suivant;
    
//     // 3. Le précédent pointe vers le nouveau
//     noeud_precedent->suivant = nouveau;
// }

// // C. SUPPRIMER UN NOEUD (par valeur)
// void supprimerNoeud(Noeud** tete_ref, int key) {
//     Noeud *temp = *tete_ref, *prev = NULL;

//     // Cas 1 : La tête contient la valeur à supprimer
//     if (temp != NULL && temp->valeur == key) {
//         *tete_ref = temp->suivant; // On déplace la tête
//         free(temp); // On libère la mémoire ! Important en C
//         return;
//     }

//     // Cas 2 : Chercher la valeur ailleurs
//     while (temp != NULL && temp->valeur != key) {
//         prev = temp;
//         temp = temp->suivant;
//     }

//     // Si la valeur n'était pas dans la liste
//     if (temp == NULL) return;

//     // On délie le noeud
//     prev->suivant = temp->suivant;
//     free(temp); // Libération mémoire
// }

// // D. TRIER LA LISTE (Tri à bulles - Bubble Sort)
// void trierListe(Noeud* tete) {
//     int echange;
//     Noeud* ptr1;
//     Noeud* lptr = NULL; // Pointeur vers le dernier noeud trié

//     if (tete == NULL) return;

//     do {
//         echange = 0;
//         ptr1 = tete;

//         while (ptr1->suivant != lptr) {
//             if (ptr1->valeur > ptr1->suivant->valeur) {
//                 // Échange des DONNÉES (plus simple que d'échanger les noeuds)
//                 int temp = ptr1->valeur;
//                 ptr1->valeur = ptr1->suivant->valeur;
//                 ptr1->suivant->valeur = temp;
//                 echange = 1;
//             }
//             ptr1 = ptr1->suivant;
//         }
//         lptr = ptr1; // Le dernier élément est maintenant à sa place
//     } while (echange);
// }

// // --- MAIN ---

// int main() {
//     Noeud* maListe = NULL; // Au début, la liste est vide

//     // 1. Construction de la liste : 3 -> 2 -> 1 -> NULL
//     ajouterDebut(&maListe, 30);
//     ajouterDebut(&maListe, 20);
//     ajouterDebut(&maListe, 10);
    
//     printf("Liste initiale :\n");
//     afficherListe(maListe);

//     // 2. Insertion entre deux (Ajouter 25 après 20)
//     // On doit d'abord trouver le noeud 20. Pour l'exemple, c'est le 2ème (maListe->suivant)
//     printf("\nInsertion de 25 après 20...\n");
//     insererApres(maListe->suivant, 25); 
//     afficherListe(maListe);

//     // 3. Suppression
//     printf("\nSuppression de 20...\n");
//     supprimerNoeud(&maListe, 20);
//     afficherListe(maListe);

//     // 4. Tri
//     printf("\nTri de la liste...\n");
//     trierListe(maListe);
//     afficherListe(maListe);
//     libererListe(maListe);
//     maListe = NULL;
//     return 0;
// }















// int compare_nodes(node_t *noeud_a, node_t *noeud_b, char **args)
// {
//     int index = 0;
//     int resultat = 0;
//     int multiplicateur = 1; // 1 pour normal, -1 pour reverse

//     TANT QUE (args[index] != NULL) FAIRE:

//         // 1. On ignore le "-r" s'il est lu comme argument principal (car déjà traité avant)
//         SI (my_strcmp(args[index], "-r") == 0) ALORS:
//             index++
//             CONTINUER la boucle

//         // 2. Vérifier si le PROCHAIN argument est "-r" pour inverser ce critère précis
//         multiplicateur = 1
//         SI (args[index + 1] != NULL ET my_strcmp(args[index + 1], "-r") == 0) ALORS:
//             multiplicateur = -1

//         // 3. Effectuer la comparaison selon le tag actuel
//         SI (my_strcmp(args[index], "TYPE") == 0) ALORS:
//             // TYPE est une chaine -> my_strcmp
//             resultat = my_strcmp(noeud_a->type, noeud_b->type)
        
//         SINON SI (my_strcmp(args[index], "NAME") == 0) ALORS:
//             // NAME est une chaine -> my_strcmp
//             resultat = my_strcmp(noeud_a->name, noeud_b->name)
        
//         SINON SI (my_strcmp(args[index], "ID") == 0) ALORS:
//             // ID est un int -> soustraction simple
//             resultat = (noeud_a->id - noeud_b->id)

//         // 4. Si les noeuds sont différents sur ce critère, on a trouvé !
//         SI (resultat != 0) ALORS:
//             RETOURNER resultat * multiplicateur

//         // 5. Sinon (égalité), on passe à l'argument suivant
//         index++
    
//     FIN TANT QUE

//     RETOURNER 0 // Les deux nœuds sont strictement identiques
// }


// void split_list(node_t *source, node_t **front_ref, node_t **back_ref)
// {
//     node_t *rapide; // Le lièvre
//     node_t *lent;   // La tortue

//     // Cas de base : Si la liste est vide ou a 1 seul élément
//     SI (source == NULL OU source->next == NULL) ALORS:
//         *front_ref = source
//         *back_ref = NULL
//         RETOURNER

//     // Initialisation
//     lent = source
//     rapide = source->next

//     // Le lièvre avance de 2, la tortue de 1
//     TANT QUE (rapide != NULL) FAIRE:
//         rapide = rapide->next
//         SI (rapide != NULL) ALORS:
//             lent = lent->next
//             rapide = rapide->next
//         FIN SI
//     FIN TANT QUE

//     // 'lent' est maintenant juste avant le milieu
//     *front_ref = source       // Le début reste le début
//     *back_ref = lent->next    // La 2ème moitié commence après 'lent'
//     lent->next = NULL         // ON COUPE le lien pour séparer les deux listes
// }


// node_t *merge(node_t *a, node_t *b, char **args)
// {
//     node_t *resultat = NULL;

//     // Cas de base : si une liste est vide, on renvoie l'autre
//     SI (a == NULL) RETOURNER b
//     SI (b == NULL) RETOURNER a

//     // On demande à compare_nodes qui doit être premier
//     // Si compare_nodes renvoie <= 0, alors 'a' est plus petit (ou égal)
//     SI (compare_nodes(a, b, args) <= 0) ALORS:
//         resultat = a
//         // On accroche la suite triée récursivement
//         resultat->next = merge(a->next, b, args)
//     SINON:
//         resultat = b
//         // On accroche la suite triée récursivement
//         resultat->next = merge(a, b->next, args)
//     FIN SI

//     RETOURNER resultat
// }

// void merge_sort(node_t **head_ref, char **args)
// {
//     node_t *head = *head_ref;
//     node_t *a = NULL;
//     node_t *b = NULL;

//     // Cas d'arrêt : liste vide ou liste de 1 élément (déjà triée)
//     SI (head == NULL OU head->next == NULL) ALORS:
//         RETOURNER

//     // 1. Couper la liste en deux sous-listes 'a' et 'b'
//     split_list(head, &a, &b)

//     // 2. Trier récursivement la sous-liste 'a'
//     merge_sort(&a, args)

//     // 3. Trier récursivement la sous-liste 'b'
//     merge_sort(&b, args)

//     // 4. Fusionner les deux moitiés triées et mettre à jour la tête principale
//     *head_ref = merge(a, b, args)
// }

// int sort(void *data, char **args)
// {
//     // ... tes vérifications d'erreurs ...
    
//     // Appel du tri
//     merge_sort(&((context_t *)data)->head, args);
    
//     return 0;
// }