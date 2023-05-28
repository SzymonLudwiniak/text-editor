SRC = ./src
INC = ./include
BIN = ./bin
LIB = ./lib
GXX = gcc
FLAGS = -Wall -Wextra -g
TARGET = $(BIN)/main
LINK = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
ARGS = testowy.txt

all:	clean build run

build:
	$(GXX) $(FLAGS) $(SRC)/*.c -o $(TARGET) $(LINK)

clean:
	rm -f $(BIN)/*

run: $(TARGET)
	$(TARGET) $(ARGS)

debug: $(TARGET)
	gdb $(TARGET) --args $(ARGS)

memtest: $(TARGET)
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 $(TARGET) $(ARGS)
