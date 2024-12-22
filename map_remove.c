#include <map.h>
#include <stdlib.h>
#include <string.h>

int map_remove(struct map_list *list, const char *key)
{
	struct dictionary_entry *current = list->head;
	struct dictionary_entry *prev = NULL;

	while (current != NULL)
	{
		
		if (strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
			{
				list->head = current->next;  // Remove the head
			}
			else
			{
				prev->next = current->next;  // Remove the node by bypassing it
			}

			
			free(current->key);
			free(current);

			return 0;
		}

		prev = current;
		current = current->next;
	}

	return -1;  // Key not found
}

