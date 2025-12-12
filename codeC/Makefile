# --- Variables de compilation ---
CC = gcc
# Flags pour le mode de développement :
# -Wall, -Wextra (tous les avertissements) -std=c11 (standard C) -g (débogage)
CFLAGS = -Wall -Wextra -std=c11 -g
# LDFLAGS : -lm est requis pour les fonctions mathématiques (comme pow, log, etc. si vous en utilisez)
LDFLAGS = -lm

# --- Fichiers ---
EXEC = cwire
SRC = main.c avl.c input.c output.c
OBJ = $(SRC:.c=.o)

# --- Règles ---

# Règle par défaut (lance la compilation)
all: $(EXEC)

# Édition de liens (Création de l'exécutable)
# ATTENTION : La ligne suivante doit commencer par une TABULATION (pas des espaces)
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilation des fichiers objets (.c -> .o)
# La dépendance header.h assure la recompilation si la structure change.
# ATTENTION : La ligne suivante doit commencer par une TABULATION
%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage (supprime les objets et l'exécutable)
# ATTENTION : La ligne suivante doit commencer par une TABULATION
clean:
	rm -f $(OBJ) $(EXEC) *.csv

# Règle pour ignorer les fichiers du même nom que les cibles (targets)
.PHONY: all clean