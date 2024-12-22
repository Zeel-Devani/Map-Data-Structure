/* Name: Devani, Zeel Jitendrabhai
 * NSID: vrp432
 * Student Number: 11387749
 * Course: CMPT214-01 2024
 */



#ifndef MAP_H
#define MAP_H
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



struct dictionary_entry
{
    char *key;
    double value;
    struct dictionary_entry *next;
};

struct map_list
{
    struct dictionary_entry *head;
    struct dictionary_entry *free_list;  // Free list retained for dynamic management
};

void map_init(struct map_list *list);

void map_deinit(struct map_list *list);

int map_add(struct map_list *list, const char *key, double value);

struct dictionary_entry* map_find(struct map_list *list, const char *key);

int map_remove(struct map_list *list, const char *key);

double map_poly(struct map_list *list, float x);

void map_print(struct map_list *list);

int map_rekey(struct map_list *list, const char *old_key, const char *new_key);

int map_add_ordered_key(struct map_list *list, const char *key, double value, int (*cmp_key)(char *item_key, char *add_key));

int map_add_ordered_value(struct map_list *list, const char *key, double value, int (*cmp_value)(double item_value, double add_value));

int map_map(struct map_list *list, int (*mutate)(struct dictionary_entry *item));

double map_reduce_right(struct map_list *list, double (*reduce)(struct dictionary_entry *item, double accumulator), double base_value);

int map_filter(struct map_list *list, int (*filter)(struct dictionary_entry *item));

int cmp_key(char *item_key, char *add_key);

int cmp_value(double item_value, double add_value);

int mutate(struct dictionary_entry *item);

double reduce(struct dictionary_entry *item, double accumulator);

int filter(struct dictionary_entry *item);

#endif

