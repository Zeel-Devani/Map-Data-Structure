# Map Data Structure

## Overview

This project implements a custom map (also known as a dictionary or hash map) using linked lists in C. It supports various operations such as adding, removing, finding, mutating, and filtering key-value pairs. The map is designed to handle both ordered and unordered maps based on keys and values, as well as support advanced features like polynomial evaluation and reduction.

The project is structured to allow the user to interact with the map through a command-line interface (CLI), or by reading commands from an input file. The map operations are implemented using basic dynamic memory management in C, ensuring flexibility and scalability.

## Features

- **Adding Elements**: Add elements to the map with `map_add`. Supports adding with ordering by key (`map_add_ordered_key`) and by value (`map_add_ordered_value`).
- **Finding Elements**: Look up an element by its key using `map_find`.
- **Removing Elements**: Remove an element by its key using `map_remove`.
- **Mutating Elements**: Apply a mutation function to modify the values of all elements in the map with `map_map`.
- **Filtering Elements**: Filter elements based on a condition with `map_filter`.
- **Rekeying**: Change the key of an existing element with `map_rekey`.
- **Polynomial Evaluation**: Evaluate a polynomial using the values stored in the map for keys 'a' to 'z' with `map_poly`.
- **Reduction**: Reduce the map values to a single result with `map_reduce_right`.
- **Command-Line Interface (CLI)**: The project provides an interactive CLI that supports various commands, or can process a sequence of commands from an input file.

## Data Structures

### `struct dictionary_entry`
Represents a key-value pair stored in the map.

- **key**: A string representing the key.
- **value**: A double representing the value associated with the key.
- **next**: A pointer to the next entry in the linked list.

### `struct map_list`
Represents the entire map, which is a linked list of `dictionary_entry` structures.

- **head**: The first element in the linked list (representing the start of the map).
- **free_list**: A free list of dictionary entries to optimize memory usage.

## Functions

### `map_init`
Initializes a new map list.

### `map_deinit`
Deinitializes the map list, freeing all dynamically allocated memory.

### `map_add`
Adds a new key-value pair to the map. Returns `0` if successful, `-1` if there’s an error (e.g., memory allocation failure).

### `map_add_ordered_key`
Adds a new key-value pair to the map, maintaining order by key using a comparison function (`cmp_key`).

### `map_add_ordered_value`
Adds a new key-value pair to the map, maintaining order by value using a comparison function (`cmp_value`).

### `map_find`
Finds a dictionary entry by its key.

### `map_remove`
Removes a key-value pair from the map by key.

### `map_poly`
Evaluates a polynomial of the form `a0 + a1*x + a2*x^2 + ... + a25*x^25`, where each coefficient is the value stored in the map for keys `'a'` to `'z'`.

### `map_map`
Applies a mutation function to each entry in the map (modifying its value).

### `map_reduce_right`
Reduces the map to a single value using a reduction function (`reduce`), starting with an initial accumulator value.

### `map_filter`
Filters entries in the map using a filter function. Elements that do not meet the filter condition are removed.

### `map_rekey`
Changes the key of an existing entry in the map.

### `map_print`
Prints all key-value pairs in the map.

## Command-Line Interface (CLI)

The program provides a CLI for interacting with the map. You can run the program in either interactive mode or batch mode (processing commands from an input file).

### Interactive Mode (`-i`)

In this mode, you can enter commands interactively. The available commands are:

- **a [a/k/v]**: Add a new entry to the map.
  - `a`: Add without order.
  - `k`: Add ordered by key.
  - `v`: Add ordered by value.
- **f [key]**: Find and print the value of a key.
- **r [key]**: Remove a key from the map.
- **l**: Apply a filter to the map (removes values that don’t satisfy the filter).
- **o [y/m/r]**: Perform an operation on the map.
  - `y`: Evaluate polynomial with the map values.
  - `m`: Mutate all map entries.
  - `r`: Perform reduction.
- **k [old_key] [new_key]**: Change the key of an entry.
- **p**: Print the current map.
- **q**: Quit the program.

### Batch Mode (`-f`)

In this mode, the program reads commands from an input file and writes results to an output file. The commands are the same as those in interactive mode.

### Example Usage

#### Interactive Mode:
```bash
$ ./map_cli -i
a a
key1 5.5
Added
f key1
Found key1 - 5.500000
r key1
Success
q
```

#### Batch Mode:
```bash
$ ./map_cli -f input.txt output.txt
```

#### Example Input File (`input.txt`):
```
a a
key1 5.5
f key1
r key1
```

#### Example Output File (`output.txt`):
```
Added
Found key1 - 5.500000
Success
```

## Compilation and Installation

1. Clone the repository.
2. Run `make` to compile the project:
   ```bash
   make
   ```

3. The executable `map_cli_static` and `map_cli_dynamic` will be available in the `bin/` directory.

4. To clean the build, run:
   ```bash
   make clean
   ```

====================================================================================================================
