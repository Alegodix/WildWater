# 💧 Projet WildWater (C-Wire)

> **Analyse et optimisation de réseaux de distribution d'eau**
> **Promotion :** Pré-Ing2 2025-2026 | **Projet :** Info 3

## 📖 Description

Ce projet est un programme un programme permettant de faire la
synthèse de données d’un système de distribution d’eau

---

## ⚙️ Compilation et Installation

### Prérequis
- Environnement Linux/Unix.
- `gcc` et `make` pour la compilation.
- `gnuplot` pour la génération des graphiques.

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
