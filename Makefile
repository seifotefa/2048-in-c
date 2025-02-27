CC = gcc
CFLAGS = -Wall -o
TARGET = game2048

all: $(TARGET)

$(TARGET): game2048.c utility.c
	$(CC) $(CFLAGS) $(TARGET) game2048.c utility.c

clean:
	rm -f $(TARGET)