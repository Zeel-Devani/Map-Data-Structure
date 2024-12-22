#include <map.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int cmp_key(char *item_key, char *add_key)
{
    return strcmp(item_key, add_key);
}

int cmp_value(double item_value, double add_value)
{
    if (item_value > add_value)
    {
        return -1;
    }
    if (item_value < add_value)
    {
        return -1;
    }
    return 0;
}

int mutate(struct dictionary_entry *item)
{
    if (item == NULL)
    {
        return 1;
    }
    item->value += item->value;
    return 0;
}

double reduce(struct dictionary_entry *item, double accumulator)
{
    return accumulator + item->value;
}

int filter(struct dictionary_entry *item)
{
    return item->value <= 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [-i | -f input_file output_file]\n", argv[0]);
        return 1;
    }

    struct map_list list;
    map_init(&list);

    char command;
    char *key = NULL;
    double value;
    float x;
    size_t len = 0;

    if (strcmp(argv[1], "-i") == 0)
    {
        // Interactive mode
        while (1)
        {
            scanf(" %c", &command);

            switch (command)
            {
            case 'a': {
                char sub_command;
                scanf(" %c", &sub_command);

                getline(&key, &len, stdin);
                key[strcspn(key, "\n")] = 0;

                scanf("%lf", &value);

                if (sub_command == 'a')
                {
                    if (map_add(&list, key, value) == 0)
                    {
                        printf("Added\n");
                    }
                    else
                    {
                        printf("Failed to add\n");
                    }
                }
                else if (sub_command == 'k')
                {
                    if (map_add_ordered_key(&list, key, value, cmp_key) == 0)
                    {
                        printf("Added with key order\n");
                    }
                    else
                    {
                        printf("Failed to add (key order)\n");
                    }
                }
                else if (sub_command == 'v')
                {
                    if (map_add_ordered_value(&list, key, value, cmp_value) == 0)
                    {
                        printf("Added with value order\n");
                    }
                    else
                    {
                        printf("Failed to add (value order)\n");
                    }
                }
                break;
            }

            case 'f':
                getline(&key, &len, stdin);
                key[strcspn(key, "\n")] = 0;

                struct dictionary_entry *entry = map_find(&list, key);
                if (entry)
                {
                    printf("Found %s - %lf\n", entry->key, entry->value);
                }
                else
                {
                    printf("Key not found\n");
                }
                break;

            case 'r':
                getline(&key, &len, stdin);
                key[strcspn(key, "\n")] = 0;

                if (map_remove(&list, key) == 0)
                {
                    printf("Success\n");
                }
                else
                {
                    printf("Fail\n");
                }
                break;

            case 'l':
                if (map_filter(&list, filter) == 0)
                {
                    printf("Filter applied\n");
                }
                else
                {
                    printf("Filter failed\n");
                }
                break;

            case 'o': {
                char sub_command;
                scanf(" %c", &sub_command);

                if (sub_command == 'y')
                {
                    scanf("%f", &x);
                    printf("Result: %lf\n", map_poly(&list, x));
                }
                else if (sub_command == 'm')
                {
                    if (map_map(&list, mutate) == 0)
                    {
                        printf("Map mutation applied\n");
                    }
                    else
                    {
                        printf("Map mutation failed\n");
                    }
                }
                else if (sub_command == 'r')
                {
                    double result = map_reduce_right(&list, reduce, 0.0);
                    printf("Reduced result: %lf\n", result);
                }
                break;
            }

            case 'k': {
                char *new_key = NULL;
                getline(&key, &len, stdin);
                key[strcspn(key, "\n")] = 0;

                getline(&new_key, &len, stdin);
                new_key[strcspn(new_key, "\n")] = 0;

                if (map_rekey(&list, key, new_key) == 0)
                {
                    printf("Success\n");
                }
                else
                {
                    printf("Fail\n");
                }

                free(new_key);
                break;  // Corrected this break
            }

            case 'p':
                map_print(&list);
                break;

            case 'q':
                map_deinit(&list);
                return 0;

            default:
                printf("Command invalid\n");
            }

            free(key);
        }
    }
    else if (strcmp(argv[1], "-f") == 0)
    {
        if (argc != 4)
        {
            printf("Usage: %s -f input_file output_file\n", argv[0]);
            return 1;
        }

        FILE *in_file = fopen(argv[2], "r");
        FILE *out_file = fopen(argv[3], "w");

        if (in_file == NULL || out_file == NULL)
        {
            printf("Error opening files\n");
            return 1;
        }

        // Read commands from the input file and write to the output file
        while (fscanf(in_file, " %c", &command) != EOF)
        {
            switch (command)
            {
            case 'a': {
                char sub_command;
                fscanf(in_file, " %c", &sub_command);

                getline(&key, &len, in_file);
                key[strcspn(key, "\n")] = 0;

                fscanf(in_file, "%lf", &value);

                if (sub_command == 'a')
                {
                    if (map_add(&list, key, value) == 0)
                    {
                        fprintf(out_file, "Added\n");
                    }
                    else
                    {
                        fprintf(out_file, "Failed to add\n");
                    }
                }
                else if (sub_command == 'k')
                {
                    if (map_add_ordered_key(&list, key, value, cmp_key) == 0)
                    {
                        fprintf(out_file, "Added with key order\n");
                    }
                    else
                    {
                        fprintf(out_file, "Failed to add (key order)\n");
                    }
                }
                else if (sub_command == 'v')
                {
                    if (map_add_ordered_value(&list, key, value, cmp_value) == 0)
                    {
                        fprintf(out_file, "Added with value order\n");
                    }
                    else
                    {
                        fprintf(out_file, "Failed to add (value order)\n");
                    }
                }
                break;
            }

            case 'f':
                getline(&key, &len, in_file);
                key[strcspn(key, "\n")] = 0;

                struct dictionary_entry *entry = map_find(&list, key);
                if (entry)
                {
                    fprintf(out_file, "Found %s - %lf\n", entry->key, entry->value);
                }
                else
                {
                    fprintf(out_file, "Key not found\n");
                }
                break;

            case 'r':
                getline(&key, &len, in_file);
                key[strcspn(key, "\n")] = 0;

                if (map_remove(&list, key) == 0)
                {
                    fprintf(out_file, "Success\n");
                }
                else
                {
                    fprintf(out_file, "Fail\n");
                }
                break;

            case 'l':
                if (map_filter(&list, filter) == 0)
                {
                    fprintf(out_file, "Filter applied\n");
                }
                else
                {
                    fprintf(out_file, "Filter failed\n");
                }
                break;

            case 'o': {
                char sub_command;
                fscanf(in_file, " %c", &sub_command);

                if (sub_command == 'y')
                {
                    fscanf(in_file, "%f", &x);
                    fprintf(out_file, "Result: %lf\n", map_poly(&list, x));
                }
                else if (sub_command == 'm')
                {
                    if (map_map(&list, mutate) == 0)
                    {
                        fprintf(out_file, "Map mutation applied\n");
                    }
                    else
                    {
                        fprintf(out_file, "Map mutation failed\n");
                    }
                }
                else if (sub_command == 'r')
                {
                    double result = map_reduce_right(&list, reduce, 0.0);
                    fprintf(out_file, "Reduced result: %lf\n", result);
                }
                break;
            }

            case 'k': {
                char *new_key = NULL;
                getline(&key, &len, in_file);
                key[strcspn(key, "\n")] = 0;

                getline(&new_key, &len, in_file);
                new_key[strcspn(new_key, "\n")] = 0;

                if (map_rekey(&list, key, new_key) == 0)
                {
                    fprintf(out_file, "Success\n");
                }
                else
                {
                    fprintf(out_file, "Fail\n");
                }

                free(new_key);
                break; 
            }

            case 'p':
                map_print(&list);
                break;

            case 'q':
                map_deinit(&list);
                fclose(in_file);
                fclose(out_file);
                return 0;

            default:
                fprintf(out_file, "Command invalid\n");
            }

            free(key);
        }

        fclose(in_file);
        fclose(out_file);
    }
    return 0;
}

