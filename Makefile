CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -g -fPIC -D_XOPEN_SOURCE=600
CPPFLAGS = -I.
BUILD_DIR = build/$(shell uname -s)-$(shell uname -m)
LIB_DIR = lib/$(shell uname -s)-$(shell uname -m)
BIN_DIR = bin/$(shell uname -s)-$(shell uname -m)
LDFLAGS = -L$(LIB_DIR) -lm

OBJS = \
    $(BUILD_DIR)/map_init.o \
    $(BUILD_DIR)/map_adder.o \
    $(BUILD_DIR)/map_process.o \
    $(BUILD_DIR)/map_remove.o \
    $(BUILD_DIR)/map_util.o \
    $(BUILD_DIR)/map_cli.o

MAP_COMMAND_OBJS = $(OBJS) $(BUILD_DIR)/map_cli.o
USER_TEST_MAP_OBJS = $(OBJS) $(BUILD_DIR)/usertestmap.o

.PHONY: all clean

all: map_cli_static map_cli_dynamic usertestmap_static

clean:
		rm -rf $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR) map_cli_dynamic* map_cli_static* usertestmap_static*
		rmdir -p build/ lib/ bin/

$(BUILD_DIR):
		mkdir -p $(BUILD_DIR)

$(LIB_DIR):
		mkdir -p $(LIB_DIR)

$(BIN_DIR):
		mkdir -p $(BIN_DIR)

# compiling object files
$(BUILD_DIR)/map_init.o: map_init.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_init.c -o $(BUILD_DIR)/map_init.o

$(BUILD_DIR)/map_adder.o: map_adder.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_adder.c -o $(BUILD_DIR)/map_adder.o

$(BUILD_DIR)/map_remove.o: map_remove.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_remove.c -o $(BUILD_DIR)/map_remove.o

$(BUILD_DIR)/map_process.o: map_process.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_process.c -o $(BUILD_DIR)/map_process.o

$(BUILD_DIR)/map_util.o: map_util.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_util.c -o $(BUILD_DIR)/map_util.o

$(BUILD_DIR)/map_cli.o: map_cli.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) map_cli.c -o $(BUILD_DIR)/map_cli.o

$(BUILD_DIR)/usertestmap.o: usertestmap.c map.h | $(BUILD_DIR)
		$(CC) -c $(CFLAGS) $(CPPFLAGS) usertestmap.c -o $(BUILD_DIR)/usertestmap.o

# libraries
$(LIB_DIR)/libmap.a: $(OBJS) | $(LIB_DIR)
		ar rcs $(LIB_DIR)/libmap.a $(OBJS)

$(LIB_DIR)/libmap.so: $(OBJS) | $(LIB_DIR)
		$(CC) -shared $(CFLAGS) $(OBJS) -o $(LIB_DIR)/libmap.so

# linking
$(BIN_DIR)/map_cli_static: $(BUILD_DIR)/map_cli.o $(LIB_DIR)/libmap.a | $(BIN_DIR)
		$(CC) $(CFLAGS) $(BUILD_DIR)/map_cli.o $(LIB_DIR)/libmap.a -lm -o $(BIN_DIR)/map_cli_static

$(BIN_DIR)/map_cli_dynamic: $(BUILD_DIR)/map_cli.o $(LIB_DIR)/libmap.so | $(BIN_DIR)
		$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-rpath $(LIB_DIR) -l:libmap.so \
			$(BUILD_DIR)/map_cli.o -lm -o $(BIN_DIR)/map_cli_dynamic

$(BIN_DIR)/usertestmap_static: $(BUILD_DIR)/usertestmap.o $(LIB_DIR)/libmap.a | $(BIN_DIR)
		$(CC) $(CFLAGS) $(BUILD_DIR)/usertestmap.o $(LIB_DIR)/libmap.a -lm -o $(BIN_DIR)/usertestmap_static

# symlink creation
map_cli_static: $(BIN_DIR)/map_cli_static
		ln -sf $(BIN_DIR)/map_cli_static map_cli_static

map_cli_dynamic: $(BIN_DIR)/map_cli_dynamic
		ln -sf $(BIN_DIR)/map_cli_dynamic map_cli_dynamic

usertestmap_static: $(BIN_DIR)/usertestmap_static
		ln -sf $(BIN_DIR)/usertestmap_static usertestmap_static

