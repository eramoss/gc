CC = clang++
CFLAGS = -Wall -Wextra -std=c++20

LIBS = -Lgenerated
INCLUDES = -Ithirdparty/dsun/src -Igenerated 

MAIN_SRC = main.cpp

BUILD_DIR = build

MAIN = $(BUILD_DIR)/main

all: $(BUILD_DIR) $(MAIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MAIN): $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SRC) $(LIBS) $(INCLUDES)

clean:
	rm -rf $(BUILD_DIR)

clang_cmd: $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- make -B


.PHONY: all clean
