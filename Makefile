CC=gcc
CFLAGS = -Wall -Wextra -O2 `sdl2-config --cflags`
LDFLAGS=-lncurses `sdl2-config --libs`

# Options de compilation
SRC=main.c map.c vehicule.c random.c MapTest.c
OBJ=$(SRC:.c=.o)
EXEC=parking

# Règle par défaut pour construire l'exécutable
all: $(EXEC)

# Règle pour lier les fichiers objets et créer l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règle pour compiler les fichiers sources en fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Commande pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Commande pour exécuter le programme
run : $(EXEC)
	./$(EXEC)

# Commandes utilisables pour le makefile
.PHONY: all clean run
