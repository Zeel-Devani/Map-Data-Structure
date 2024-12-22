#include <map.h>

void map_init(struct map_list *list)
{
	list->head = NULL;
	list->free_list = NULL;
}

void map_deinit(struct map_list *list)
{
	if (!list)
	{
		return;
	}

	struct dictionary_entry *current = list->head;
	struct dictionary_entry *next = NULL;

	while (current != NULL)
	{
		next = current->next;

		free(current->key);
		free(current);

		current = next;
	}

	list->head = NULL;
}



