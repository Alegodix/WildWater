#include "avl.h"

pArbre creerArbre(char* ID) { //créée un arbre et lui assigne l'ID en paramètre + valeurs NULL autrement; 
	pAVL nouveau = malloc(sizeof(AVL));
  	nouveau->u->ID = ID;
  	nouveau->u->capte = nouveau->u->conso = nouveau->u->capacitemax = 0;
	nouveau->fg = nouveau->fd = NULL;
	nouveau->eq = 0;
	return nv;
}

int max(int a, int b) { //retourne le max entre a et b deux entiers; OK
	if (a > b) return a;
	else return b;
}

int min(int a, int b) { //même chose pour le minimum entre deux entiers; OK
	if (a =< b) return a;
	else return b;
}


pAVL rotationgauche(pAVL a) { //fais une rotation gauche de l'AVL entré en paramètre; OK
    int eq_a = 0;
    int eq_p = 0;
    pAVL pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->eq;
    eq_p = pivot->eq;
    a->eq = eq_a - max(eq_p, 0) - 1;
    pivot->eq = min(eq_a - 2, min(eq_a + eq_p - 2, eq_p - 1));
    a = pivot;
    return a;
}

pAVL rotationdroite(pAVL a) { //fait une rotation droite de l'AVL entré en paramètre; OK
    int eq_a = 0;
    int eq_p = 0;
    pAVL pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->eq;
    eq_p = pivot->eq;
    a->eq = eq_a - min(eq_p, 0) + 1;
    pivot->eq = max(eq_a + 2, max(eq_a + eq_p + 2, eq_p + 1));
    a = pivot;
    return a;
}

pAVL doublerotationgauche(pAVL a) { // fait une double rotation gauche de l'AVL entré en paramètre; OK 
    a->fd = rotationdroite(a->fd);
    return rotationgauche(a);
}

pAVL doublerotationdroite(pAVL a){ // fait une double rotation gauche de l'AVL entré en paramètre; OK
    a->fg = rotationgauche(a->fg);
    return rotationdroite(a);
}
pAVL equilibrerAVL(pAVL a) { //équilibre l'AVL à l'aide des fctions de rotation si déséquilibre (vérifie si il y a déséquilibre aussi); OK normalement
	if (a != NULL) {
		if (a->equilibre <= -2) {
			if (a->fg->equilibre <= 0) {
				return rotationDroite(a);
			} else {
				return rotationDroiteDouble(a);
			}
		} else if (a->equilibre >= 2) {
			if (a->fd->equilibre >= 0) {
				return rotationGauche(a);
			} else {
				return rotationGaucheDouble(a);
			}
		}
	}
	return a;
}
/*
Comment insérer dans l’AVL:

// Exemple théorique de comparaison 
int resultat = strcmp(identifiant_nouveau, noeud_actuel->usine.id); 
if (resultat < 0) {                        // L'identifiant est "plus petit" alphabétiquement -> Aller à GAUCHE 
} else if (resultat > 0) {              // L'identifiant est "plus grand" alphabétiquement -> Aller à DROITE 
} else {                                       
        // resultat == 0 : C'est la même usine ! 
        // On ne crée pas de nouveau noeud, on met à jour les données (somme des volumes) }
*/
pAVL insertionAVL(pAVL a, char* ID, int* h) { //insère un élément dans l'AVL INCOMPLET A MODIFIER 
	if (a == NULL) {
		*h = 1;
		return creerArbre(ID);
	}
	if (ID < a->value) {
		a->fg = insertionAVL(a->fg, ID, h);
		*h = -*h;
	} else if (v > a->value) {
		a->fd = insertionAVL(a->fd, ID, h);
	} else {
		*h = 0;
		return a;
	}
	if (*h != 0) {
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL(a);
		if (a->equilibre == 0) {
			*h = 0;
		} else {
			*h = 1;
		}
		
	}
	return a;
}
