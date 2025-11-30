# Makefile compatível com MinGW (Windows)
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I./src

SRC = src/main.c src/board.c src/fleet.c src/game.c src/io.c src/rnd.c
OBJ = $(SRC:.c=.o)
TARGET = batalha.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@if exist src\*.o del /Q src\*.o
	@if exist $(TARGET) del /Q $(TARGET)
	@-rm -f src/*.o batalha 2>nul || true

run: all
	@echo Executando...
	@$(TARGET)
