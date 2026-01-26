/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** hashtable.h
*/

#ifndef HASHTABLE_H
    #define HASHTABLE_H

    #include <stdlib.h>
    #include <stdio.h>
    #define MAGIC_NUMBER 5381
    #define HASH_MIXER 2654435761

typedef struct entry_s {
    char *key;
    char *value;
    struct entry_s *next;
} entry_t;

typedef struct hashtable_s {
    int len;
    int (*hash)(char *, int);
    entry_t **buckets;
} hashtable_t;

// Hash function
int hash(char *key, int len);

// Create & destroy table
hashtable_t *new_hashtable(int (*hash) (char *, int), int len);
void delete_hashtable(hashtable_t *ht);

// Handle table
int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);

#endif /* HASHTABLE_H */
