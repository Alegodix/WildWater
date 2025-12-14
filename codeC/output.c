#include "header.h"
#include "couleurs.h" // Ajout de l'inclusion des couleurs

/*
Écrit les données d'une usine dans le fichier selon le mode choisis (src, max, real).
Utilisée par outputHisto.
*/
void afficherNoeud(Usine* u, FILE* fichier, char* mode) {
    if (u == NULL || fichier == NULL) exit(1);
    double valeur = 0;
    if (strcmp(mode, "src") == 0) {
        valeur = u->volumeSource;
    } else if (strcmp(mode, "max") == 0) {
        valeur = u->capacite;
    } else if (strcmp(mode, "real") == 0) {
        valeur = u->volumeTraite;
    } else {
        //msg d'erreur aur cas où
        fprintf(stderr, ROUGE "Erreur interne: Mode '%s' non reconnu par afficherNoeud.\n" RESET, mode);
        return; 
    }
    
    // On n'affiche que si la valeur est supérieure à zéro (pour la clarté de l'histogramme)
    if (valeur > 0) {
        fprintf(fichier, "%s;%.3f\n", u->ID, valeur / 1000.0);
    }
}


/*
Écrit les données d'une usine dans le fichier pour le rapport de fuites.
Utilisée par outputLeaks.
*/
void afficherNoeudLeaks(Usine* u, FILE* fichier) {
    if (u == NULL || fichier == NULL) exit(1); 
    if (u->capacite > 0 && u->volumeTraite > u->capacite) { // Ajout u->capacite > 0 pour éviter division par zéro/cas invalides
        double diff = u->volumeTraite - u->capacite;
        fprintf(fichier, "%s;%.3f;%.3f;%.3f\n", u->ID, u->capacite / 1000.0, u->volumeTraite / 1000.0, diff / 1000.0);
    }
}

/*
Ecrit les données dans l'ordre alphabétique inverse des identifiants.
*/
void parcoursInfixeInverse(pAVL a, FILE* fichier, char* mode) {
  if (a != NULL) {
    parcoursInfixeInverse(a->fd, fichier, mode);
    afficherNoeud(a->u, fichier, mode);
    parcoursInfixeInverse(a->fg, fichier, mode);
  }
}

/*
Ecrit les données dans l'ordre alphabétique des identifiants.
*/
void parcoursInfixe(pAVL a, FILE* fichier) {
    if (a != NULL) {
        parcoursInfixe(a->fg, fichier);
        afficherNoeudLeaks(a->u, fichier);
        parcoursInfixe(a->fd, fichier);
    }
}

/* 
Générer le fichier CSV pour faire l'histogramme
*/
void outputHisto(char* nomFichier, pAVL a, char* mode) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) { //ajout message d'erreur au cas où
        fprintf(stderr, ROUGE "Erreur : Impossible de créer le fichier %s\n" RESET, nomFichier);
        exit(1);
    }

    // Ecriture de l'en-tête CSV
    if (strcmp(mode, "src") == 0) {
        fprintf(fichier, "identifier;volume source(M.m3.year-1)\n");
    } else if (strcmp(mode, "max") == 0) {
        fprintf(fichier, "identifier;capacite(M.m3.year-1)\n");
    } else if (strcmp(mode, "real") == 0) {
        fprintf(fichier, "identifier;volume traite(M.m3.year-1)\n");
    } else { //ajout message d'erreur au cas où
        fprintf(stderr, ROUGE "Erreur : Mode '%s' non reconnu.\n" RESET, mode);
        fclose(fichier);
        exit(1);
    }

    // Ecriture des données
    parcoursInfixeInverse(a, fichier, mode);
    
    fclose(fichier);
    printf(VERT "Fichier %s généré.\n" RESET, nomFichier);
}

void outputLeaks(char* nomFichier, pAVL a) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        fprintf(stderr, ROUGE "Erreur : Impossible de créer le fichier %s\n" RESET, nomFichier);
        exit(1);
    }

    // Ecriture de l'en-tête CSV
    fprintf(fichier, "Station;Capacite (M.m3);Volume Traite (M.m3);Surplus (M.m3)\n"); 

    // Ecriture des données
    parcoursInfixe(a, fichier);
    
    fclose(fichier);
    // Ajout du message de succès
    printf(VERT "Fichier %s généré.\n" RESET, nomFichier);
}