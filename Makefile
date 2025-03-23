CC = gcc
CFLAGS = -Wextra -Wall -I "C:\SDL2-2.32.2-dev\x86_64-w64-mingw32\include"
LDFLAGS = -L "C:\SDL2-2.32.2-dev\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2
SRC_DIR = src
BUILD_DIR = build
EXE_NAME = game.exe

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

all: $(BUILD_DIR)/$(EXE_NAME)

$(BUILD_DIR)/$(EXE_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	del /q $(BUILD_DIR)\*

run: all
	$(BUILD_DIR)/$(EXE_NAME)
