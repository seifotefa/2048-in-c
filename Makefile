CC = gcc
CFLAGS = -Wall -std=c11
SRC_DIR = src
OBJ_DIR = obj

all: game2048

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

game2048: $(OBJ_DIR)/game2048.o $(OBJ_DIR)/utility.o
	$(CC) $(CFLAGS) -o game2048 $(OBJ_DIR)/game2048.o $(OBJ_DIR)/utility.o

$(OBJ_DIR)/game2048.o: $(SRC_DIR)/game2048.c $(SRC_DIR)/utility.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/game2048.c -o $(OBJ_DIR)/game2048.o

$(OBJ_DIR)/utility.o: $(SRC_DIR)/utility.c $(SRC_DIR)/utility.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utility.c -o $(OBJ_DIR)/utility.o

clean:
	rm -rf $(OBJ_DIR) game2048
