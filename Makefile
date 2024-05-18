TARGET = dse

CC = gcc
CFLAGS = -Wall
NCURSES_FLAGS = -lncursesw

SRC_DIR = src
OBJ_DIR = obj/src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(NCURSES_FLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)

.PHONY: all clean