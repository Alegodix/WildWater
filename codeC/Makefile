# --- Variables de compilation ---
CC = gcc
# -Wall -Wextra : Active tous les avertissements (rigueur attendue)
# -std=c11 : Standard moderne du C
# -g : Ajoute les symboles de débogage (utile pour gdb/valgrind)
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

# --- Fichiers --

# Nom de l'exécutable final
EXEC = cwire

# Liste des fichiers sources
SRC = main.c avl.c input.c output.c
# Transformation automatique .c -> .o
OBJ = $(SRC:.c=.o)

# --- Règles ---

# Règle par défaut (lancée par 'make')
all: $(EXEC)

# Édition de liens (Création de l'exécutable)
$(EXEC): $(OBJ)
	@echo "Création de l'exécutable $(EXEC)..."
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation des fichiers objets (.c -> .o)
# La dépendance header.h force la recompilation si le header change
%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage (Obligatoire selon le sujet [cite: 260])
clean:
	@echo "Nettoyage des fichiers temporaires..."
	rm -f $(OBJ) $(EXEC)

# Phony targets pour éviter les conflits de noms de fichiers
.PHONY: all clean