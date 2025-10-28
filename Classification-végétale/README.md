# Classification végétale – Analyse de données écologiques

Projet réalisé en partenariat avec le laboratoire **BIORECA** (Martinique) dans le cadre de la rédaction d’un article scientifique sur la biodiversité végétale et les espèces invasives.

## Objectif

Étudier la structure des peuplements végétaux et prédire leur dominance à partir de variables environnementales (altitude, température, type de sol, etc.) à l’aide de modèles de classification supervisée.

## Contexte scientifique

- **Jeux de données** : 52 522 observations réparties sur 11 communes de Martinique
- **Taxonomie** : 526 espèces, 130 familles botaniques
- **Répartition géographique** :
  - Sud : 89.7 %
  - Nord : 10.3 %

## Mon rôle

- Nettoyage, structuration et exploration des données
- Analyse de la distribution des espèces et des classes de dominance
- Sélection de variables environnementales pertinentes
- Implémentation et évaluation de modèles de classification (Random Forest, SVM)
- Rédaction du rapport scientifique et visualisation des résultats

## Technologies utilisées

- **Langage** : Python 3
- **Librairies** : pandas, scikit-learn, matplotlib, seaborn, numpy
- **Modèles** : Random Forest, SVM

## Résultats clés

- **Accuracy Random Forest** : 72.4 % (20 variables)
- **Accuracy SVM** : 71.8 %
- **Variables explicatives majeures** : altitude, température, type de sol
- **Espèces invasives** : 4 espèces à risque élevé identifiées

## Structure du dépôt
classification-vegetale/  
├── data/ # Données brutes (non incluses ici)  
├── notebooks/ # Notebooks Jupyter d’analyse  
├── src/ # Scripts Python (prétraitement, modèles, visualisations)  
├── figures/ # Graphiques et cartes générés  
├── rapport_scientifique.txt  
└── README.md


## Limites et recommandations

- Données déséquilibrées (93 % de classes "dominantes")
- Absence de validation externe indépendante
- Recommandation : enrichir les données avec des sources de télédétection et standardiser les protocoles d’inventaire

## Perspectives

Ce projet constitue une base opérationnelle pour la **surveillance écologique** et la **prévention des espèces invasives** en milieu tropical. Il pourra être étendu à d’autres territoires ou couplé à des données satellitaires.

---

## Auteur

**Alexy Bernard**  
Master 2 Intelligence Artificielle – Université des Antilles  
Martinique/Guadeloupe  
alexybernard.ab@gmail.com
