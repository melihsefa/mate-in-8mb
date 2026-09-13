CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic -Wconversion -Wshadow
SAN     := -fsanitize=address,undefined -fno-omit-frame-pointer
CFLAGS  := $(CSTD) $(WARN) -Iinclude -g
LDFLAGS :=

SRC_DIR   := src
TEST_DIR  := tests
BUILD_DIR := build

# All engine sources except main.c (kept separate so tests can link
# against the engine without pulling in main's entry point)
ENGINE_SRCS := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
ENGINE_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(ENGINE_SRCS))

MAIN_SRC := $(SRC_DIR)/main.c
MAIN_OBJ := $(BUILD_DIR)/main.o

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRCS))

TARGET := chess

.PHONY: all debug release test clean run

all: $(TARGET)

# Default build includes sanitizers (desktop dev target from the spec)
debug: CFLAGS += $(SAN) -O0
debug: $(TARGET)

release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

$(TARGET): $(ENGINE_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Tests -------------------------------------------------------------
# Each test file is compiled together with the engine objects (minus main)
# into its own standalone binary, then run immediately.

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		./$$t || exit 1; \
	done

$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(ENGINE_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SAN) $< $(ENGINE_OBJS) -o $@ $(LDFLAGS)

# --- Utility -------------------------------------------------------------

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
