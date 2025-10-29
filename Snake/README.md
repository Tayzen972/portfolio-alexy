# Snake – Mini-projet algorithmique en Python

Ce projet a été réalisé dans le cadre du module **Algorithmique et Programmation 1 (AP1)** en L1 Informatique à l’Université Paris-Est. Il s’agit d’un clone du célèbre jeu Snake, enrichi de plusieurs fonctionnalités avancées.

## Objectif

Développer un jeu Snake en Python avec interface graphique, en respectant les règles classiques du jeu tout en ajoutant des éléments de difficulté et de stratégie.

## Fonctionnalités principales

- Déplacement du serpent via les flèches directionnelles
- Apparition aléatoire de pommes normales toutes les 3 secondes
- Croissance du serpent à chaque pomme mangée
- Détection de collision avec les murs, le corps du serpent ou les bords de la fenêtre
- Accélération progressive du jeu en fonction du score
- Affichage du score en temps réel
- Apparition de **pommes empoisonnées** (rouges) qui réduisent le score
- Apparition d’**obstacles temporaires** à éviter

## Technologies utilisées

- **Langage** : Python 3
- **Librairie graphique** : `upemtk` (interface fournie par l’université)
- **Environnement** : Terminal / éditeur de texte

## Répartition du travail

Projet réalisé en binôme :
- **Alexy Bernard** : gestion du mouvement du serpent, affichage des objets, logique de collision, accélération du jeu
- **Alexandre Bellegueille** : croissance du serpent, gestion des pommes mangées, détection de collision avec le corps
- Programmation principale et boucle de jeu développées à deux

## Difficultés rencontrées

- Synchronisation du corps du serpent avec sa tête
- Gestion des collisions complexes (corps, murs, bordures)
- Accélération du jeu en fonction du score
- Implémentation du mode deux joueurs (non finalisé)

## Améliorations possibles

- Mode multijoueur avec serpents infinis
- Arène torique (type Pac-Man)
- Menu de sélection des modes de jeu
- Système de rejouabilité en fin de partie

---

## Auteurs

**Alexy Bernard**  
Étudiant en L1 Informatique  
Université Paris-Est

**Alexandre Bellegueille**  
Étudiant en L1 Informatique  
Université Paris-Est
