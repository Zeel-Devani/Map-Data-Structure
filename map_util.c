#include <map.h>
#include <stdio.h>
#include <string.h>

/*
 * Purpose: Print all key-value pairs in the map list
 * Pre-conditions: A valid map_list pointer
 * Post-conditions: None
 * Return: None
 */
void map_print(struct map_list *list)
{
	struct dictionary_entry *current = list->head;

	// Print each entry in the list
	while (current != NULL)
	{
		// Dynamically print the key and its value, as the key length is variable
		printf("%s -> %f\n", current->key, current->value);
		current = current->next;
	}
}

