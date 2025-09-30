CC = clang++
CFLAGS = -Wall -Wextra -std=c++20

LIBS = -Lgenerated
INCLUDES = -Igenerated 

MAIN_SRCS = main.cpp 

BUILD_DIR = build
MAIN = $(BUILD_DIR)/gc

GENERATED_SRCS = $(wildcard generated/*.cpp)
GENERATED_OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(GENERATED_SRCS)) 

all: $(BUILD_DIR) $(MAIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(MAIN_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/generated/%.o: generated/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MAIN): $(BUILD_DIR)/main.o $(GENERATED_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(BUILD_DIR)

clang_cmd: $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- make -B


test: $(MAIN)
	python ./tests/runner.py


.PHONY: all clean clang_cmd
