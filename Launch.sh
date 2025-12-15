#!/bin/bash

# Nom de l'exécutable (Doit correspondre au Makefile)
EXEC="codeC/cwire" #
MAKEFILE="Makefile"

# Fonction d'affichage de l'aide
show_help() {
    echo "Usage du script c-wire :"
    echo "  $0 <fichier.csv> histo <max|src|real>"
    echo "      -> Génère un histogramme des volumes."
    echo "  $0 <fichier.csv> leaks <identifiant_usine>"
    echo "      -> Affiche les fuites pour une usine spécifique."
    echo "  $0 -h"
    echo "      -> Affiche cette aide."
    exit 0
}

# 0. Gestion de l'aide (-h)
if [ "$1" == "-h" ]; then
    show_help
fi

# 1. Vérification des arguments
if [ "$#" -ne 3 ]; then
    echo "Erreur : Nombre d'arguments incorrect (3 attendus)."
    echo "Tapez '$0 -h' pour l'aide."
    exit 1
fi

DATA_FILE="$1"
COMMAND="$2"
ARGUMENT="$3"

# Vérification de l'existence du fichier de données
if [ ! -f "$DATA_FILE" ]; then
    echo "Erreur : Le fichier de données '$DATA_FILE' est introuvable."
    exit 1
fi

# 2. Vérification et Compilation
# On nettoie d'abord pour être sûr d'avoir une version propre (optionnel mais recommandé)
if [ ! -f "$EXEC" ] && [ ! -f "$EXEC.exe" ]; then
    echo "Compilation du programme C en cours..."
    make
    if [ $? -ne 0 ]; then
        echo "Erreur critique : La compilation a échoué."
        exit 1
    fi
fi

# Début du chronométrage
start_time=$(date +%s%N)

# 3. Traitement selon la commande
if [ "$COMMAND" = "histo" ]; then

    # Vérification de la validité du mode
    if [[ "$ARGUMENT" != "max" && "$ARGUMENT" != "src" && "$ARGUMENT" != "real" ]]; then
        echo "Erreur : Mode '$ARGUMENT' invalide pour histo. (Choix : max, src, real)"
        exit 1
    fi

    echo "Traitement 'histo' en mode '$ARGUMENT'..."

    # Exécution du programme C
    # Note : Sur Git Bash, ./cwire fonctionne même si le fichier est cwire.exe
    ./$EXEC "$DATA_FILE" "$COMMAND" "$ARGUMENT"
    RET=$?

    if [ $RET -ne 0 ]; then
        echo "Erreur lors de l'exécution du programme C (Code $RET)."
        exit $RET
    fi

    # Détermination du nom du fichier de sortie généré par le C
    if [ "$ARGUMENT" == "src" ]; then CSV_OUT="vol_source.csv"; fi
    if [ "$ARGUMENT" == "max" ]; then CSV_OUT="vol_max.csv"; fi
    if [ "$ARGUMENT" == "real" ]; then CSV_OUT="vol_real.csv"; fi

    # Génération du graphique Gnuplot
    if [ -f "$CSV_OUT" ]; then
        echo "Génération du graphique pour $CSV_OUT..."
        
        # Configuration Gnuplot :
        # - separator ';' : car vos CSV sont séparés par des points-virgules
        # - skip 1 : pour ignorer la ligne d'en-tête (identifier;volume...)
        # - xtic(1) : utilise la colonne 1 (ID usine) comme étiquette X
        # - style data histogram : pour faire des barres
        # - yrange [0:*] : pour que l'axe Y commence à 0
        
        gnuplot -e "
            set terminal png size 1200,800 enhanced font 'Arial,10';
            set output '${ARGUMENT}.png';
            set datafile separator ';';
            set title 'Histogramme : $ARGUMENT';
            set xlabel 'Usines';
            set ylabel 'Volume (M.m3)';
            set style data histograms;
            set style fill solid 1.0 border -1;
            set boxwidth 0.9;
            set xtics rotate by -45 scale 0;
            set grid y;
            set yrange [0:*];
            plot '$CSV_OUT' using 2:xtic(1) notitle linecolor rgb '#3366CC';
        "
        echo "Graphique généré avec succès : ${ARGUMENT}.png"
    else
        echo "Erreur : Le fichier $CSV_OUT n'a pas été généré par le programme C."
    fi

elif [ "$COMMAND" = "leaks" ]; then
    echo "Traitement 'leaks' pour l'usine : $ARGUMENT..."
    
    # Appel du programme C (commande leaks à implémenter plus tard dans le C)
    ./$EXEC "$DATA_FILE" "$COMMAND" "$ARGUMENT"
    RET=$?
    
    if [ $RET -ne 0 ]; then
        echo "Erreur ou alerte lors du calcul des fuites (Code $RET)."
    else
        echo "Calcul des fuites terminé."
    fi

else
    echo "Erreur : Commande '$COMMAND' inconnue."
    show_help
fi

# 4. Affichage du temps d'exécution
end_time=$(date +%s%N)
# Calcul de la durée en secondes (avec virgule flottante pour précision)
# Astuce pour Git Bash/Linux : on utilise bc ou awk, ou une simple soustraction bash
duration=$(( (end_time - start_time) / 1000000 )) ; # en millisecondes

echo "Durée totale : ${duration} ms"