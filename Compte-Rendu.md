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
### Les dates
#### Date.h
Ce fichier contient les définitions des prototypes des fonctions destinée à traiter les dates, ainsi que l'implémentation de la structure `Date`.

Ce fichier est construit de la manière suivante :

1. Macro Guard
2. Inclusions
3. Implémentation de la structure
4. Commantaire sur le prototype
	de la fonction qui vas être
	définit dessous
5. prototype d'une fonction

#### Date.c
Ce fichier contient les implémentations des fonction prototypées dans `Date.h`

Ce fichier est construit de la manière suivante :
1. Inclusions
2. Implémentation des fonctions

Les fonction proposé dans ce fichier sont :
```c
Date lireDate(FILE* flux)
```
&uarr; Cette fonction (*lireDate*) permet de lire une date dans un flux.
Cette fonction est souvent utilisée lors de lecture de fichiers.
En effet, lorsque que le curseur servant à lire le fichier se trouve devant une
date, il suffit d'appeler liredate(). Elle est aussi appelé lors du lancement du programme pour entrer la date du jours sur le flux *stdin*. **Aucun problème relevé pour cette fonction**

```c
void afficherDate(Date date, FILE* flux)
```
&uarr; Cette fonction(*afficherDate*) permet d'écrire une date sur un flux.
Elle est souvent utilisée lors de sauvegarde de données dans des fichiers ou dans l'affichage de structure comprenant des dates (Adherant, Réservation, Emprunt...).
En effet, lorsque que le curseur servant à écrire dans le fichier se trouve sur le point d'écrire une date, il suffit d'appeler afficherDate().**Aucun problème relevé pour cette fonction**

```c
int dateCmp(Date date1, Date date2)
```
&uarr; Cette fonction(*dateCmp*), permet de comparer 2 dates. Cette fonction a été plutôt difficile à implémenter du fait de l'irrégularité du nombre de jours dans un mois.
En effet, cette fonction doit retourner le nombre de jours qui c'est écoulé entre deux dates.**Plus aucun problèmes relevés pour cette fonction**

```c
Date *plusPetiteDate(Date *date1, Date *date2)
```
&uarr; Cette fonction (*plusPetiteDate*) permet de comparer 2 dates et de retourner l’adresse de la date la plus petite (la moins récente). En effet, elle compare chaque champs d'une date pour savoir quelle date retourner. **Aucun problème relevé pour cette fonction**

```c
Date *plusGrandeDate(Date *date1, Date *date2)
```
&uarr; Cette fonction (*plusGrandeDate*) permet de comparer 2 dates et de retourner l’adresse de la date la plus grande (la plus récente). En effet, elle compare chaque champs d'une date pour savoir quelle date retourner. **Aucun problème relevé pour cette fonction**

### Les adherants
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
