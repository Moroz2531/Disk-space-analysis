TARGET = dse

CC = gcc
CFLAGS = -Wall -Werror

SRC_DIR = src
OBJ_DIR = obj/src
BIN_DIR = bin

clean:
	rm $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)