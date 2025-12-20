# 💧 Projet WildWater (C-Wire)

> **Analyse et optimisation de réseaux de distribution d'eau**
> **Promotion :** Pré-Ing2 2025-2026 | **Projet :** Info 3

## 📖 Description

Ce projet implémente une solution performante en **Langage C** et **Shell** pour traiter des fichiers de données massifs (plusieurs millions de lignes) représentant le réseau de distribution d'eau. Il utilise des structures de données avancées (**AVL**, Listes chaînées) pour optimiser les temps de traitement, générer des histogrammes de capacité et détecter les fuites d'eau.

---

## ⚙️ Compilation et Installation

### Prérequis
* Environnement Linux/Unix.
* `gcc` et `make` pour la compilation.
* `gnuplot` pour la génération des graphiques.

### Commandes de build
Pour compiler le projet et générer l'exécutable, placez-vous à la racine du projet et exécutez :
- make clean && make
- Pour générer 
- ./Launch.sh <fichier.csv> <histo|leaks> <arguments>

## 🚀 Utilisation

Le programme s'exécute via le script principal `Launch.sh`. Il gère automatiquement la compilation (via le `Makefile`) si l'exécutable n'est pas à jour.

### 1. Préparation
Avant la première utilisation, assurez-vous que le script possède les droits d'exécution :

```bash
chmod +x Launch.sh
