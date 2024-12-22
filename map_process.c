#include <map.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct dictionary_entry* map_find(struct map_list *list, const char *key)
{
	struct dictionary_entry *current = list->head;

	while (current != NULL)
	{
		if (strncmp(current->key, key, strlen(key)) == 0)
		{
			return current;
		}
		current = current->next;
	}

	return NULL;
}

double map_poly(struct map_list *list, float x)
{
	double result = 0.0;

	for (int i = 0; i < 26; i++)
	{
		char key[2] = { 'a' + i, '\0'};

		struct dictionary_entry *entry = map_find(list, key);

		double coef = (entry != NULL) ? entry->value : 0.0;

		result += coef * pow(x, i);
	}

	return result;
}

int map_map(struct map_list *list, int (*mutate)(struct dictionary_entry *item))
{
	if (!list || !mutate)
	{
		return -1;
	}

	struct dictionary_entry *current = list->head;

	while (current)
	{
		if (!mutate(current))
		{
			return -1;
		}

		current = current->next;
	}

	return 0;
}

double map_reduce_right(struct map_list *list, double(*reduce)(struct dictionary_entry *item, double accumulator), double base_value)
{
	if (!list || !reduce)
	{
		return -1;
	}

	struct dictionary_entry *current = list->head;
	double accumulator = base_value;

	while (current)
	{
		accumulator = reduce(current, accumulator);
		current = current->next;
	}

	return accumulator;
}

int map_filter(struct map_list *list, int (*filter)(struct dictionary_entry *item))
{
	if (!list || !filter)
	{
		return -1;
	}

	struct dictionary_entry *prev = NULL;
	struct dictionary_entry *current = list->head;

	while (current)
	{
		if (filter(current) == 0)
		{
			if (prev)
			{
				prev->next = current->next;
			}
			else
			{
				list->head = current->next;
			}

			struct dictionary_entry *to_remove = current;
			current = current->next;
			to_remove->next = list->free_list;
			list->free_list = to_remove;

			free(to_remove->key); 
			to_remove->key = NULL;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}

	return 0;
}


int map_rekey(struct map_list *list, const char *old_key, const char *new_key)
{
	struct dictionary_entry *current = list->head;

	while (current != NULL)
	{
		if (strncmp(current->key, old_key, strlen(old_key)) == 0)
		{
			char *new_key_copy = (char *)malloc(strlen(new_key) + 1);
			if (new_key_copy == NULL)
			{
				return -1;
			}

			free(current->key);
			strcpy(new_key_copy, new_key);
			current->key = new_key_copy;

			return 0;
		}

		current = current->next;
	}

	return -1;
}

