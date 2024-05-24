TARGET = dse

CC = gcc
CFLAGS = -Wall
NCURSES_FLAGS = -lncursesw

ROOT_PATH = /usr/local/bin

SRC_DIR = src
OBJ_DIR = obj/src
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(BIN_DIR)/$(TARGET)
	sudo make install

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(NCURSES_FLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ 

install : $(BIN_DIR)/$(TARGET)
	install -D -m 755 $(BIN_DIR)/$(TARGET) $(ROOT_PATH)

clean:
	rm $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)
	sudo rm $(ROOT_PATH)/$(TARGET)

.PHONY: all clean install