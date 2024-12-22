#include <map.h>


int map_add(struct map_list *list, const char *key, double value)
{
	if (list->free_list == NULL)
	{
		return -1; // No space available
	}

	// Allocate a new entry from free_list and set up new entry's kv pair
	struct dictionary_entry *new_entry = (struct dictionary_entry *)malloc(sizeof(struct dictionary_entry));
	if (new_entry == NULL)
	{
		return -1;
	}

	new_entry->key = strdup(key);
	if (new_entry->key == NULL)
	{
		free(new_entry);
		return -1;
	}

	new_entry->value = value;
	new_entry->next = NULL;

	if (list->head == NULL)
	{
		list->head = new_entry;
	}
	else
	{
		struct dictionary_entry *current = list->head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_entry;
	}

	return 0;
}



int map_add_ordered_key(struct map_list *list, const char *key, double value, int (*cmp_key)(char *item_key, char *add_key))
{
	if (!list || !key || !cmp_key)
	{
		return -1;
	}

	struct dictionary_entry *new_entry = (struct dictionary_entry *)malloc(sizeof(struct dictionary_entry));
	if (new_entry == NULL)
	{
		return -1;
	}

	new_entry->key = strdup(key);
	if (new_entry->key == NULL)
	{
		free(new_entry);
		return -1;
	}
	
	new_entry->value = value;
	new_entry->next = NULL;

	struct dictionary_entry **current = &(list->head);
	
	while (*current && cmp_key((*current)->key, new_entry->key) < 0)
	{
		current = &((*current)->next);
	}
	
	new_entry->next = *current;
	*current = new_entry;



	return 0;
}

int map_add_ordered_value(struct map_list *list, const char *key, double value, int (*cmp_value)(double item_value, double add_value))
{
    if (!list || !key || !cmp_value)
    {
        return -1; // Invalid parameters
    }

    
    struct dictionary_entry *new_entry = (struct dictionary_entry *)malloc(sizeof(struct dictionary_entry));
    
    if (new_entry == NULL)
    {
        return -1;
    }

    
    new_entry->key = strdup(key);
    if (new_entry->key == NULL)
    {
	    free(new_entry);
	    return -1;
    }

    new_entry->value = value;
    new_entry->next = NULL;

    
    struct dictionary_entry **current = &(list->head);

    while (*current && cmp_value((*current)->value, new_entry->value) < 0)
    {
        current = &((*current)->next);
    }

    new_entry->next = *current;
    *current = new_entry;

    return 0;
}

