CC = gcc
# [MODIF] Ajout de l'option -I pour indiquer le chemin du dossier 'include' à gcc.
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
LDFLAGS = -lm

OBJ = codeC/main.o codeC/avl.o codeC/input.o codeC/output.o
EXEC = codeC/cwire

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# [MODIF IMPORTANTE] : Suppression de la dépendance explicite à codeC/header.h
# On suppose maintenant que l'include dans les .c est "#include "header.h""
# et que gcc trouvera ce fichier grâce au CFLAGS -Iinclude
codeC/%.o: codeC/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(EXEC).exe *.csv *.png