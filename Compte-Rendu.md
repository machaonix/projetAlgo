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

----
## Fonctions concernant les dates et les adhérents
### Les dates
#### Tout d'abord
L'implémentation des dates de trouve dans les fichiers `source/Date.h` et `source/Date.c`.
#### Structure des fichiers
Le fichier d'entête (*source/Date.h*) débute par une *marco guard* affin de protéger le fichier des inclusions multiples. S'en suit les inclusions nécessaires au bon fonctionnement du code (*stdio.h*, *stdlib.h* et *CodeErreur.h*) puis l'implémentation de la structure `Date`. La suite du fichier consiste à commenter les prototypes des fonctions qui sont définis en dessous de ces commentaires.

Le fichier source (*source/Date.c*) inclue simplement son fichier d'entête et contient ensuite l'implémentation commentée des fonctions prototypées dans le fichier d'entête.

#### La structure `Date`
```c
typedef struct {
  int jour;
  int mois;
  int annee;
} Date;
```
Cette structure contient simplement 3 entiers représentant les éléments que l'on trouve dans une date, à savoir `jour`, `mois` et `année`.

#### Fonctionnalités avec `Date`

Les `Date`s n'ont pas de fonctionnalités propre proposé dans le menu mais elle servent au bon déroulement du programme.

### Les adhérants
#### Tout d'abord
L'implémentation des dates de trouve dans les fichiers `source/Adherant.h` et `source/Adherant.c`.

#### Structure des fichiers
Le fichier d'entête (*source/Adherant.h*) débute par une *marco guard* affin de protéger le fichier des inclusions multiples. S'en suit les inclusions nécessaires au bon fonctionnement du code (*stdio.h*, *stdlib.h*, *Bool.h*, *Date.h* et *CodeErreur.h*) puis l'implémentation de l'énumération `Civilite` et  de la structure `Adherant`. La suite du fichier consiste à commenter les prototypes des fonctions qui sont définis en dessous de ces derniers.

Le fichier source (*source/Adherant.c*) inclue simplement son fichier d'entête et contient ensuite l'implémentation commentée des fonctions prototypées dans le fichier d'entête.

#### La structure `Adherant`
```c
typedef struct
{
	unsigned int id;
	Civilite civilite;
	char nom[22];
	char prenom[22];
	Date dateInscri;
} Adherant;
```
La structure `Adherant` est composée des champs requis permettant la sauvegarde de cette structure.

Les `Adherant`s serons par la suite stocké dans un tableau dynamiquement alloué. Ce choix a été fait car les `Adherant`s seron plus lus que modifier et car de nouveaux `Adherant`s peuvent venir s'ajouter au fur et à mesure du temps.

#### Fonctionnalités avec `Adherant`
```c
void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete);
Adherant nouvAdherant(unsigned int id, Date dateDuJour);
CodeErreur renouvelerInscription(Adherant* ad, Date* nouvelleDate);
CodeErreur sauvegarderAdherant(Adherant tAdherant[], unsigned int nbElem, char nomDuFichier[]);
```
Tout ces fonctions sont proposées dans le menu et sont toutes opérationnelles. Elles permettent ainsi le bon déroulement du programme. Aucune de ces fonctions n'ont posées problème lors de leur implémentation.

Voici le restes des fonctions qui servent au fonctions implémentées si dessus :
```c
Adherant lireAdherant(FILE* flux);
void afficheAdherant(Adherant ad, FILE* flux, Bool entete);
int insererAdherant(Adherant* tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad);
int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int id);
void decalageAGaucheAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);
void decalageADroiteAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);
unsigned int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int id, Bool* trouve);
int chargerLesAdherants(Adherant* tAdherant[], unsigned int* tMax, char nomDuFichier[]);
Bool checkInscriptionValide(Adherant* ad, Date* dateDuJour);
CodeErreur copieTabAdherant(Adherant tAdherant1[], unsigned int nbElem1, Adherant tAdherant2[], unsigned int tMax2);
unsigned int rechercherIDAdherantLibre(Adherant tAdherant[], unsigned int nbElem);
```
Ici, plusieurs fonctions on était problématique lors de leurs implémentation. En effet, les fonction `copieTabAdherant` et `insererAdherant` m'ont posées problème. Je(*Allan POINT*) n'arivait pas à réallouer le tableaux dans la fonction `copieTabAdherant` et donc j'ai du le faire dans `insererAdherant`. C'est pour cette raison que `copieTabAdherant` renvoit **ERR_OUT_OF_RANG** en cas d'erreur.

----

## Fonctions concernant les emprunts et les réservations

### Structure emprunt et réservation

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
Les emprunts et les réservations contiennent les mêmes variables, on peut donc utiliser la même structure pour les deux. De plus, le type de la structure porte plusieurs nom selon le contexte (si on définie un emprunt ou une réservation).

Pour traiter cette structure, plusieurs fonctions sont disponibles dont voici les prototypes.

```c
EmpruntReservation lireEmpruntReservation(FILE* flux); //Lit un emprunt ou une réservation depuis un flux.
void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux);//Affiche un emprunt ou une réservation dans un flux.
```

Passer le flux en paramètre permet de pouvoir réunir la fonction d'affichage à l'écran et la fonction d'écriture en une seul. Le paramètre flux est donc prévue pour prendre deux arguments possibles:

* flux &rarr; qui sera un flux vers le fichier dans lequel on souhaite écrire
* stdout &rarr; flux vers la sortie standard (écran)

### Listes contenant les emprunts et les réservations

Les emprunts et les réservations sont contenus dans des listes, qui permettent une manipulation plus fluide d'un point de vue mémoires que les tableaux, car une liste n'a pas de taille pré-définie.

```c
typedef struct element
{
	EmpruntReservation empRes;
	struct element* suiv;
} Element, *ListeReservation, *ListeEmprunt, *ListeER;
```
Là aussi, le type porte plusieurs nom selon le contexte à la définition.

Chaque liste est initialisé grâce à la fonction ``ListeER listeER_Vide(void);``.
Pour savoir si une liste est vide, il y a la fonction ``Bool listeER_estVide(ListeER liste);`` qui renvoit TRUE si la liste est vide.

###### Fonction d'affichage

Il existe deux fonctions pour afficher une liste.
```c
void afficherListeEmpruntReservation(ListeER liste, FILE* flux,int nb);
void afficherListeERJeu(ListeER liste, unsigned int idJeu);
```
La première fonction affiche une liste en entière. Elle est aussi utilisée pour écrire dans les fichiers de données lors de la sauvegarde (en précisant un flux vers un fichier).

La seconde fonction affiche uniquement sur la sortie standard les éléments d'une liste concernant un jeu donné.

###### Fonction de chargement
----
## Traitement des jeux

### Préambule
Mon objectif principal était de permettre une certaine versatilité en terme d'accès aux jeux. Pour cela je me suis concentré sur les systèmes de tri et de recherche.

### Petit point sur les fichiers
Les headers  ``TableauJeu.h`` et ``Jeu.h`` disposent de header guard. Ils incluent tout deux ``CodeErreur.h`` et ``Bool.h`` en plus de quelques headers standards.\
``TableauJeu.c`` et ``Jeu.c`` n'incluent que leur ``.h``respectifs.

### Les fichiers Jeu.h et Jeu.c
#### Jeu : une structure simple
##### La structure
La structure jeu représente un jeu (et ses exemplaires)
```C
typedef struct
{
    unsigned int id;
    char nom[41];
    char type[15];
    unsigned int nbExemplaireTotal;
    unsigned int nbExemplaireDispo;
} Jeu;
```
La strucure de jeu est composé des éléments requis auquels s'ajoute le nombre d'exemplaires disponibles. Cette variable permet de s'avoir efficacement si un jeu est disponible ou non.\
Le type de jeu (ou categorie) n'est pas contraint pour offrir une place au genres de niche pouvant exister.

##### Les fonctions associées
```C
Jeu* lireJeu(FILE* flux);
void afficheJeu(Jeu* jeu, FILE* flux);
Jeu* nouvJeu(unsigned int id);

void copyJeu(Jeu* jd, Jeu* js);
Jeu* allocJeu(void);
```
Les 3 premières fonctions offrent les fonctionnalités basique d'entrée sortie pour la structure Jeu.\
Les 2 dernières concernent plus la gestion des ressources.\
Même si j'essaie de copier le plus rarement possible les jeux, lorsque c'est necessaire il faut que ce soit bien fait. Jeu contenant des chaines de caractères, j'ai crée copyJeu.\
L'allocation mémoire pouvant être sensible je l'ai encapsulé dans allocJeu de manière à ne pas multiplié les possibilité d'erreurs.

#### ElementJeu : une enumération facilitant les opérations
##### L'enumération
ElementJeu permet d'indiquer une des elements de la structure Jeu
```C
typedef enum { ELEM_JEU_NONE , ELEM_JEU_ID, ELEM_JEU_NOM, ELEM_JEU_TYPE, ELEM_JEU_NB_EXEMPLAIRE_TOTAL, ELEM_JEU_NB_EXEMPLAIRE_DISPO} ElementJeu;
```
Cette enumération offre au fonctions sur les jeux la capacité d'agir sur les differentes variables des jeux avec plus de simplicité (et de manière uniforme). Toute les variables de Jeu y sont référencées, et "aucune" est représenté par ELEM_JEU_NONE.
##### Les fonctions liées
Ces trois fontions permettent de factoriser le code concernant ElementJeu.
```C
ElementJeu choisirElementJeu(char utilite[]);
Bool elementJeuExiste(ElementJeu elementJeu, Bool noneAutorisee);
void afficheAllElementJeu();
```

#### Des fonctions associant Jeu et ElementJeu
```C
CodeErreur entrerValeurElementJeu(Jeu* jeu, ElementJeu elementJeu);
int jeuCmp(Jeu* j1, Jeu* j2, ElementJeu elementJeu);
```

jeuCmp défini l'ordre entre les jeux selon les éléments.\
entrerValeurElementJeu facilite l'entrée d'une valeur pour tous les elements.
