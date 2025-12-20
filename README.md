# 💧 Projet WildWater (C-Wire)

> **Projet d'Info 3** - Analyse et optimisation de réseaux de distribution d'eau.  
> **Promotion :** Pré-Ing2 2025-2026

## 📖 Description

Ce projet implémente une solution performante en **Langage C** et **Shell** pour traiter des fichiers de données massifs (plusieurs millions de lignes) représentant le réseau de distribution d'eau. Il utilise des structures de données avancées (**AVL**, Listes chaînées) pour optimiser les temps de traitement, calculer les fuites et générer des histogrammes via Gnuplot.

---

## ⚙️ Installation et Compilation

### Prérequis
* Système : **Linux** / Unix
* Compilateur : **gcc**
* Outils : **make**, **gnuplot**

### Instructions de compilation
Placez-vous à la racine du projet et exécutez les commandes suivantes :

1. Nettoyer l'environnement (supprimer les anciens exécutables et fichiers objets) :
   ```bash
   make clean
