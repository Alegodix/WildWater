#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct usine {
  char* ID;
  float capte;
  float capacitemax;
  float conso;
}Usine;
typedef struct avl {
  struct *Usine u;
  struct *avl fg;
  struct *avl fd;
  int eq;
}AVL, *pAVL;

Arbre* creerArbre(char* id, float ct, float capamax, float cs);

Arbre* insertionAVL(pAVL a, char* id, float volume, int* h);

Arbre* equilibreAVL(pAVL a);

void libererArbre(pAVL a);

void afficherArbreInverse(pAVL a);

int max(int a, int b);
int min(int a, int b);
