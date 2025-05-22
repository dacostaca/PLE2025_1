CC = gcc
SRC_DIR = ../src
OBJ_DIR = ../obj
BIN_DIR = ./bin

CFLAGS = -I$(SRC_DIR)

all: $(BIN_DIR)/tui_test

$(BIN_DIR)/tui_test: src/tui_test.c $(OBJ_DIR)/tui.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/tui.o: $(SRC_DIR)/tui.c $(SRC_DIR)/tui.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/tui.o $(BIN_DIR)/tui_test
