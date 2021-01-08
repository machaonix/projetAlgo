# Compte Rendu du Projet d'algorithmie et de structure de données.
Tâches:
* Point Allan G5
  - Fonctions de traitement des dates
  - Fonctions de traitement des adhérants
* Ribémont Mathis G5
  - Fonctions de traitement des emprunts et des réservations
  - Fonctions de traitement des listes d'emprunts et de réservations
* Rouault Martin G5
  - Fonctions de traitement des jeux.
  - Fonctions de traitement des tableaux de jeux

Sujet: programme aidant la gestion des adhérents, des emprunts et des réservations d'une ludothèque.

## Fonctions concernant les dates et les adhérents



## Fonctions concernant les emprunts et les réservations

#### Structure emprunt et réservation

Les emprunts et les réservations sont issue de la structure
dans ``EmpruntReservation.h``
```c
typedef struct
{
    unsigned int id;
    unsigned int idAdherant;//reference un adherant
    unsigned int idJeu;//reference à un jeu
    Date date;
} Emprunt, Reservation, EmpruntReservation;
```
Les emprunts et les réservations contiennent les mêmes variables, on peut donc utiliser la même structure pour les deux.

Pour traiter cette structure, plusieurs fonctions sont disponibles dont voici les prototypes.

```c
EmpruntReservation lireEmpruntReservation(FILE* flux); //Lit un emprunt ou une réservation depuis un flux.
void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux);//Affiche un emprunt ou une réservation dans un flux.
```

Passer le flux en paramètre permet de pouvoir réunir la fonction d'affichage à l'écran et la fonction d'écriture en une seul. Le paramètre flux est donc prévue pour prendre deux arguments possibles:

* flux -> qui sera un flux vers le fichier dans lequel on souhaite écrire
* stdout -> flux vers la sortie standard (écran)

#### Listes contenant les emprunts et les réservations

## Fonctions concernant les jeux
