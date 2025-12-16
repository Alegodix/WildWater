#include "header.h"
#include <ctype.h>
#define BUFFER_SIZE 4096

/*
Supprimer le caractère de saut de ligne final (\n ou \r)
*/
void nettoyerLigne(char* chaine) {
  char* p = strchr(chaine, '\n');
  if (p != NULL) *p = '\0';
  p = strchr(chaine, '\r');
  if (p != NULL) *p = '\0';
}

/*
Vérifier si une chaîne est un nombre valide
*/
int estNumerique(char* chaine) {
  if (chaine == NULL || strlen(chaine) == 0) return 0;
  if (strcmp(chaine, "-") == 0) return 0;
  // On vérifie le premier caractère (chiffre ou signe négatif)
  return (isdigit(chaine[0]) || chaine[0] == '-');
}

/*
Retourne un pointeur vers le noeud dans l'arbre ou le crée s'il n'existe pas.
*/
pUsine trouverOuCreer(pAVL* a, char* ID) {
  pUsine usineExistante = rechercher(*a, ID);
  if (usineExistante != NULL) return usineExistante;
  Usine temp;
  memset(&temp, 0, sizeof(Usine));
  strncpy(temp.ID, ID, 49);
  int h = 0;
  *a = insertionAVL(*a, temp, &h);
  return rechercher(*a, ID);
}

/*
Charger les données pour faire l'histogramme des sources.
*/
void chargerDonnees(char* cheminFichier, pAVL* a, char* commande, char* mode) {
  FILE* fichier = fopen(cheminFichier, "r");
  if (fichier == NULL) {
    fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", cheminFichier);
    exit(1);
  }

  printf("Le fichier a ete ouvert sans erreur\n");
  
  char ligne[BUFFER_SIZE];
  char ligne_copie[BUFFER_SIZE];
  
  int histoActive = (strcmp(commande, "histo") == 0);
  int leaksActive = (strcmp(commande, "leaks") == 0);
  
  while (fgets(ligne, BUFFER_SIZE, fichier) != NULL) {
    nettoyerLigne(ligne);
    if (strlen(ligne) == 0) continue;
    strcpy(ligne_copie, ligne);

    char* col1 = strtok(ligne_copie, ";");
    char* col2 = strtok(NULL, ";");
    char* col3 = strtok(NULL, ";");
    char* col4 = strtok(NULL, ";");
    char* col5 = strtok(NULL, ";");

    // On vérifie si la ligne est valide
    if (col1 == NULL || col2 == NULL || col3 == NULL || col4 == NULL) continue;
    if (!estNumerique(col4)) continue;

    // On initialise les variables pour stocker les données de la ligne 
    char* idUsine = NULL;
    double capacite = 0;
    double volume = 0;
    int lignePertinente = 0;
    
    // ====================================================
    // LOGIQUE DE SELECTION DES LIGNES SELON LE MODE
    // La fonction atof convertit une chaîne de caractère en double.
    // La fonction memset initialise les valeurs à 0.
    // ====================================================

    if (histoActive) {
        
        // 1. Détection d'une ligne de CAPACITÉ
        // Format attendu : - ; ID_USINE ; - ; CAPACITE ; -
        // L'usine est bien dans la 2ème colonne (col2)
        if (strcmp(col3, "-") == 0 && strcmp(col2, "-") != 0) {
            pUsine u = trouverOuCreer(a, col2); // On utilise col2
            u->capacite = atof(col4);
        }
        
        // 2. Détection d'une ligne de TRAJET (Flux)
        // Format attendu : - ; SOURCE ; DESTINATION ; VOLUME ; FUITE
        else if (strcmp(col3, "-") != 0 && strcmp(col2, "-") != 0) {
            // En mode SRC ou REAL, on s'intéresse au trajet
            if (strcmp(mode, "src") == 0 || strcmp(mode, "real") == 0) {
                // Ici, l'usine qui REÇOIT l'eau est en 3ème colonne (col3)
                pUsine u = trouverOuCreer(a, col3); 
                double volumeBrut = atof(col4);
                
                if (strcmp(mode, "src") == 0) {
                   u->volumeSource += volumeBrut;
                } else if (strcmp(mode, "real") == 0) {
                   double fuite = 0.0;
                   if (col5 != NULL && estNumerique(col5)) {
                       fuite = atof(col5);
                   }
                   u->volumeTraite += volumeBrut * (1.0 - (fuite / 100.0));
                }
            }
        }
    }
    // CAS 3 : Mode LEAKS
    // [MODIFICATION] On charge TOUT le graphe, pas juste l'usine de départ.
    // Si on filtre ici, on ne connaitra pas les enfants des enfants.
    else if (leaksActive) {
      // Si col3 n'est pas "-", c'est un tuyau (connexion Parent -> Enfant)
      if (strcmp(col3, "-") != 0) {
        pUsine parent = trouverOuCreer(a, col2);
        pUsine enfant = trouverOuCreer(a, col3);
        
        // On lit le pourcentage de fuite (colonne 5)
        double fuite = (col5 && estNumerique(col5)) ? atof(col5) : 0.0;
        
        // On ajoute la connexion dans l'arbre
        ajouterVoisin(parent, enfant, fuite);
      }
      
      // Si c'est une ligne qui définit la capacité d'une usine (ex: Usine; - ; - ; Capacité ; -)
      // C'est important pour récupérer le volume de départ de l'usine cible.
      else if (strcmp(col2, "-") != 0 && strcmp(col4, "-") != 0) {
         pUsine u = trouverOuCreer(a, col2);
         u->capacite = atof(col4);
      }
    }
  }
  fclose(fichier);
}
