# Compte Rendu du Projet d'algorithmie et de structure de données.

Répartition des tâches:
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
## Généralité

#### Le type Booléen

Un type booléen a été créé pour certain cas d'utilisation.
```c
typedef enum {FALSE, TRUE}Bool;
```

#### Les codes erreurs

Pour simplifier et uniformiser la gestion des codes erreurs, une énumération de codes erreurs a été créé.
A posteriori nous pensons qu'il aurait été intéressant de créer un fonction affichant les messages appropriés au différent code.

```c
typedef enum {ERR_OUVERTURE_FICHIER=-10, ERR_ALLOCATION /*-9*/,...} CodeErreur;
```

#### Choix

Cette fonction permet de poser une question "Oui/Non" de manière simple, la fonction gérant les tests sur l'entrée.
```c
Bool IO_Choix_O_N(char message[]);
```
Cette fonction test si les caractères ``O`` (pour oui) ou ``N`` (pour non) sont entrés par l'utilisateur. Le message en paramètre est la question posée sans ``?``.

#### Date du jour
La date du jour est demandée à l'utilisateur au début du programme pour le bon fonctionnement du de ce dernier. En effet, grâce à cela, il est possible de transmettre la date du jour à n'importe quelle partie du code en faisant passer cette date par argument lors d’appel de fonctions qui on besoin de cette date pour fonctionner.

----

## Fonctionnalités pour les utilisateurs finaux

### Généralités
Les différentes fonctionnalités sont accessibles à partir d'un menu. Les fonctions suivantes se chargent respectivement de l'affichage et du traitement des entrées de celui ci.
```C
void afficheMenu(void);
void Ludotheque(void);
```
La liste des fonctionnalités est représentée par l'énumération suivante.
```C
typedef enum {CHOIX_ANNULER_RESERVATION =1 , CHOIX_EMPRUNTER, CHOIX_RETOUR_JEU, CHOIX_AFFICHE_JEU,
    CHOIX_TRIER_JEU, CHOIX_AJOUTER_JEU, CHOIX_MODIFIER_SUPPRIMER_JEU, CHOIX_NOUV_ADHERANT,
    CHOIX_RENOUV_ADHERANT, CHOIX_AFFICHE_ADHERANT, CHOIX_AFFICHE_EMPRUNT, CHOIX_AFFICHE_RESERVATION,
    CHOIX_AFFICHE_RESERVATION_JEU, CHOIX_AFFICHE_EMPRUNT_JEU, CHOIX_SAUVEGARDER, CHOIX_QUITTER} ChoixAction;
```

La fonction ``void Ludotheque(void)`` se charge aussi d'initialiser, de charger et de libérer toutes les listes et tableaux stockant adhérants, emprunts, reservations et jeux.

## Sauvegarder et quitter
``CHOIX_SAUVEGARDER`` et ``CHOIX_QUITTER`` dans l'énumération ChoixAction
```C
void GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherant tAdherant[], unsigned int nbElemAdhearant,
    ListeReservation liste_Reservation, int nb_Reservation,
    ListeEmprunt liste_Emprunt, int nb_Emprunt);
```
La fonction ``GLOBAL_Sauvegarder`` est responsable de la sauvegarde des differentes données.

```C
case CHOIX_QUITTER:
    if (IO_Choix_O_N("Souhaitez vous sauvegarder avant de quitter"))
        GLOBAL_Sauvegarder(&tabJeu, tAdherant, nbElemAdhearant, liste_Reservation, nb_Reservation,
            liste_Emprunt, nb_Emprunt);
    lance = FALSE;
    break;
```
Il n'y a pas de fonction pour quitter. Il est proposé de sauvegarder avant de quitter.

## Affichage
``CHOIX_AFFICHE_JEU``
``CHOIX_AFFICHE_ADHERANT``
``CHOIX_AFFICHE_EMPRUNT``
``CHOIX_AFFICHE_RESERVATION``
Ces 4 affichages utilise les fonctions d'affichages fournies avec les différentes structures.

``CHOIX_AFFICHE_RESERVATION_JEU``
``CHOIX_AFFICHE_EMPRUNT_JEU``
Ces deux fonctionnalités d'affichage utilisent une fonction globale.

```C
void GLOBAL_afficherListeERJeu_Interactif(ListeER liste, TableauJeu* tabJeu, Bool isReservation)
```
Permet la recherche d'un jeu pour lequel afficher les reservations ou les emprunts associés.
On fait passer un booléen à la fonction pour savoir si il s'agit d'afficher des réservations ou des emprunts, de manière à modifier l'affichage en conséquence.


## Gestion des jeux
``CHOIX_TRIER_JEU`` ``CHOIX_AJOUTER_JEU``
Ces deux fonctionnalités s'appuient uniquement sur des fonctions de TableauJeu

 ``CHOIX_MODIFIER_SUPPRIMER_JEU``
Celle ci requiert differents tests sur les emprunts et les reservations pour éviter de corrompre leurs listes respectives.
```C
Bool GLOBAL_ModifierSupprimerJeu(TableauJeu* tabJeu, ListeReservation* liste_Reservation,
    unsigned int *nb_Reservation, ListeEmprunt liste_Emprunt);
```
``GLOBAL_ModifierSupprimerJeu`` se charge donc d'assurer la cohérance d'une suppression ou d'une modification de jeu.

## Gestion des adhérants
### Ajouter un `Adherant`
C'est la fonction `GLOBAL_NouvelAdherant` qui s'occupe d'ajouter un `Adherant` dans le tableau d’adhérants si il n'est pas déjà enregistré. Elle retourne un booléen pour indiquer si l'`Adherant` a bien était ajouté.
```c
Bool GLOBAL_NouvelAdherant(Adherant* tAdherant[], int* nbElemAdhearant,
	 unsigned int* tMaxAdherant, unsigned int* rangNouvAdherant, Date dateDuJour)
```
### Renouveler un abonnement
C'est la fonction `GLOBAL_RenouvellerAdherant` qui s'occupe de renouveler un abonnement. Elle demande un montant et renouvelle l’abonnement en fonction de ce dernier. Elle renvoi un booléen pour indiquer si tout c'est bien passé.
```c
Bool GLOBAL_RenouvellerAdherant(Adherant tAdherant[], unsigned int nbElemAdhearant)
```

## Emprunt et réservation de jeux

Voici les différentes fonctionnalités que l'utilisateur peut utiliser.

#### Emprunter et réserver

Pour emprunter un jeu, on utilise la fonction
```c
Bool GLOBAL_Emprunter(ListeReservation* liste_Reservation,
  unsigned int* nb_Reservation, ListeEmprunt* liste_Emprunt,
  unsigned int* nb_Emprunt, TableauJeu* tabJeu, Adherant* tAdherant[],
  int* nbElemAdhearant, unsigned int* tMaxAdherant, Date dateDuJour)
```
Si il n'y a pas d'exemplaire du jeu disponible, on demande à l'utilisateur s'il doit créer une réservation. Si oui, une réservation est créée.

#### Annuler une réservation

```c
Bool GLOBAL_Anuller_Reservation(ListeReservation* lr,
  unsigned int* nb_Reservation, Adherant tAdherant[],
  unsigned int nbElemAdhearant, TableauJeu* tabJeu)
```
Cette fonction permet d'annuler une réservation en demandant les informations à l'utilisateur.

#### Retourner un jeux

```c
Bool GLOBAL_RetourJeu(Adherant tAdherant[], unsigned int nbElemAdhearant,
  TableauJeu* tabJeu, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt,
  ListeReservation* liste_Reservation, Date dateDuJour)
```
Cette fonction permet de retourner un jeu. Si des réservations du jeu rendu existent, la plus ancienne réservation est donc transformé en emprunt.

----

## Fonctions concernant les dates et les adhérents
### Les dates
#### Tout d'abord
L'implémentation des dates de trouve dans les fichiers `source/Date.h` et `source/Date.c`.
#### Structure des fichiers
Le fichier d'entête (*source/Date.h*) débute par une *header guard* affin de protéger le fichier des inclusions multiples. S'en suit les inclusions nécessaires au bon fonctionnement du code (*stdio.h*, *stdlib.h* et *CodeErreur.h*) puis l'implémentation de la structure `Date`. La suite du fichier consiste à commenter les prototypes des fonctions qui sont définis en dessous de ces commentaires.

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
Le fichier d'entête (*source/Adherant.h*) débute par un *header guard* affin de protéger le fichier des inclusions multiples. S'en suit les inclusions nécessaires au bon fonctionnement du code (*stdio.h*, *stdlib.h*, *Bool.h*, *Date.h* et *CodeErreur.h*) puis l'implémentation de l'énumération `Civilite` et  de la structure `Adherant`. La suite du fichier consiste à commenter les prototypes des fonctions qui sont définis en dessous de ces derniers.

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
CodeErreur copieTabAdherant(Adherant tAdherant1[], unsigned int nbElem1,
	Adherant tAdherant2[], unsigned int tMax2);
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
EmpruntReservation lireEmpruntReservation(FILE* flux);
void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux);
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
Pour savoir si une liste est vide, il y a la fonction ``Bool listeER_estVide(ListeER liste);`` qui renvoit TRUE si la liste est vide. Enfin, les listes sont triées par identifiant des emprunts et des réservations.

##### Fonction d'affichage

Il existe deux fonctions pour afficher une liste.
```c
void afficherListeEmpruntReservation(ListeER liste, FILE* flux,int nb);
void afficherListeERJeu(ListeER liste, unsigned int idJeu);
```
La première fonction affiche une liste en entière. Elle est aussi utilisée pour écrire dans les fichiers de données lors de la sauvegarde (en précisant un flux vers un fichier), justifiant le paramètre ``nb`` (nombre d'élément dans la liste).

La seconde fonction affiche uniquement sur la sortie standard les éléments d'une liste concernant un jeu donné.

##### Fonction de chargement

Le chargement des fichiers d'emprunts et de réservations est assuré par la fonction
```c
chargerListeEmpruntReservation(char nomDeFichier[], unsigned int *nb);
```
.
Cette fonction prend en paramètre une chaîne de caractères ``nomDeFichier`` qui sera utilisé pour créer le flux vers le fichier dans lequel sont sauvegardées les données à charger. La fonction prend aussi en paramètre un pointeur vers la variable dans laquelle sera enregistrée le nombre d'éléments dans la liste.
Il faut appeler cette fonction pour chaque liste a créer.

Cette fonction fait appel à la fonction ``lireEmpruntReservation(FILE* flux)`` pour lire dans le fichier.

##### Fonction d'insertion

Pour insérer un élément dans une liste, il faut appeler la fonction
```c
ListeER insererEmpruntReservation(ListeER liste, unsigned int *nb, EmpruntReservation er);
```
Elle prend en paramètre la liste dans laquelle on insère l'élément, un pointeur sur le nombre d'élément dans la liste, et l'emprunt ou la reservation à insérer. Cette fonction utilise la fonction
```c
ListeER insererDevantEmpruntReservation(ListeER liste, EmpruntReservation er);
```

##### Suppression d'un élément

La suppression d'un élément se passe de la même manière avec deux fonctions.
```c
ListeER supprimerEmpruntReservation(ListeER liste, unsigned int id, unsigned int *nb, CodeErreur* cErr);
ListeER supprimerDevantEmpruntReservation(ListeER liste);
```

La différence ici c'est qu'on fait passer un l'id de l'élément à supprimer au lieu d'un emprunt ou d'une réservation. On lui fait aussi passer un pointeur vers une variable ``cErr`` pour retourner un code erreur si besoin.

##### Les fonctions de recherche

Plusieurs fonction de recherche existent selon ce qu'on recherche et les informations qu'on possède.
```c
unsigned int rechercherIdLibre(ListeER liste);
unsigned int rechercherListeER_AdJeu(ListeER liste, unsigned int idAdherant, unsigned int idJeu, Bool* trouve);
unsigned int rechercherListeER_Jeu(ListeER liste, unsigned int idJeu, Bool* trouve);
```
La fonction ``rechercherIdLibre()`` permet de rechercher le premier identifiant libre (inutilisé) de la liste qu'on lui passe, ce qui permet de garder les liste trié par identifiant. Cette identifiant servira à définir un nouvel élément à insérer dans la liste.

La fonction ``rechercherListeER_AdJeu()`` permet de rechercher un élément, selon l'identifiant du jeu emprunté et l'identifiant de l’adhérent qui a emprunté le jeu.
Cette fonction retourne l'identifiant de l'élément. Elle permet aussi de savoir avec le pointeur ``trouve`` si l'élément a été trouvé ou non.

La fonction ``rechercherListeER_Jeu`` permet de rechercher un élément selon un identifiant de jeu. Cette fonction est surtout utilisé pour savoir si un emprunt ou une réservations existe avec le jeu donné.

##### Réservation la plus ancienne

Quand un jeu est retourné par un adhérent, on recherche les réservations du jeu rendu pour changer la plus ancienne réservation en emprunt. Pour récupérer la réservation la plus ancienne, il faut utiliser la fonction suivante
```c
Reservation plusVieilleReservationJeu(ListeReservation liste_Reservation, unsigned int idJeu);
```

##### Sauvegarde

```c
CodeErreur sauvegarderListeER(ListeER liste, char nomDeFichier[], int nb);
```
Cette fonction écrit une liste dans un fichier dont le nom est donné par la chaîne de caractère ``nomDeFichier``. Elle prend en paramètre ``nb``, le nombre d'éléments dans la liste. Pour écrire dans le fichier, la fonction utilise ``afficherListeEmpruntReservation()``. Comme décrite plus tôt, cette fonction prend en paramètre un flux (fichier ou stdout) et le nombre d'élément dans la liste.

##### Fin du programme

Tous les éléments des listes sont créés par allocation dynamique. Pour supprimer tous ces éléments, il faut utilisé la fonction suivante
```c
ListeER supprimerListe(ListeER liste);
```
Cette fonction va libérer la mémoire pour chaque élément de la liste qui lui est passée. Elle retourne ``NULL`` quand tous les éléments de la liste sont supprimés.

----

## Traitement des jeux

### Préambule
Mon objectif principal était de permettre une certaine versatilité en terme d'accès aux jeux. Pour cela je me suis concentré sur les systèmes de tri et de recherche.

### Petit point sur les fichiers
Les headers  ``source/TableauJeu.h`` et ``source/Jeu.h`` disposent de header guard. Ils incluent tout deux ``source/CodeErreur.h`` et ``source/Bool.h`` en plus de quelques headers standards.
``source/TableauJeu.c`` et ``source/Jeu.c`` n'incluent que leur ``.h``respectifs. Ils contiennent les commentaires des fonctions

##### Note au lecteur
Les termes Jeu et structure Jeu seront tout deux utilisés pour designer la structure Jeu. De même pour la structure TableauJeu.

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
La strucure de jeu est composé des éléments requis auquels s'ajoute le nombre d'exemplaires disponibles. Cette variable permet de s'avoir efficacement si un jeu est disponible ou non.
Le type de jeu (ou categorie) n'est pas contraint pour offrir une place au genres de niche pouvant exister.

##### Les fonctions associées
```C
Jeu* lireJeu(FILE* flux);
void afficheJeu(Jeu* jeu, FILE* flux);
Jeu* nouvJeu(unsigned int id);

void copyJeu(Jeu* jd, Jeu* js);
Jeu* allocJeu(void);
```
Les 3 premières fonctions offrent les fonctionnalités basique d'entrée sortie pour la structure Jeu.
Les 2 dernières concernent plus la gestion des ressources.
Même si j'essaie de copier le plus rarement possible les jeux, lorsque c'est necessaire il faut que ce soit bien fait. Jeu contenant des chaines de caractères, j'ai crée copyJeu.
L'allocation mémoire pouvant être sensible je l'ai encapsulé dans allocJeu de manière à ne pas multiplié les possibilité d'erreurs.

#### ElementJeu : une enumération facilitant les opérations
##### L'enumération
ElementJeu permet d'indiquer une des elements de la structure Jeu
```C
typedef enum { ELEM_JEU_NONE , ELEM_JEU_ID, ELEM_JEU_NOM, ELEM_JEU_TYPE,
    ELEM_JEU_NB_EXEMPLAIRE_TOTAL, ELEM_JEU_NB_EXEMPLAIRE_DISPO} ElementJeu;
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

jeuCmp défini l'ordre entre les jeux selon les éléments.
entrerValeurElementJeu facilite l'entrée d'une valeur pour tous les elements.


### Les fichiers TableauJeu.h et TableauJeu.c

#### TableauJeu : Un tableau entouré
##### La structure
TableauJeu contient un tableau de jeux et les données necessaires à son fonctionnement
```C
#define TAILLE_MAX_TAB_JEU 100

typedef struct
{
	unsigned int nbElement;
	ElementJeu triSur;
	Jeu* jeux[TAILLE_MAX_TAB_JEU];
} TableauJeu;
```
Le tableau à proprement parler est un tableau statique de pointeurs vers des Jeu. Sa taille est défini par une macro du préprocesseur (Ce qui permet de l'utiliser dans les fonctions en ayant besoin).
Nous avons choisi un tableau de pointeurs pour éviter un maximum la copie des Jeu durant les nombreux tris effectué sur le tableau de jeux.
Le nombre de jeux dans le tableau est stocké dans la variable nbElement.
TableauJeu contient aussi une variable ElementJeu indiquant si et comment le tableau est ordonné.

##### Les fonctions sur TableauJeu
Les fonctions ayant besoin d'un TableauJeu prennent un pointeur sur un TableauJeu de manière à éviter de copier la structure.

###### Initialisation et libération
```C
void initTabJeu(TableauJeu* tabJeu);
void libererTabJeu(TableauJeu* tabJeu);
```
Ces deux fonctions sont à appeller respectivement à la création et à la fin de vie du TableauJeu.

###### Chargement et sauvegarde

```C
CodeErreur chargerTabJeu(TableauJeu* tabJeu, char nomFichier[]);
CodeErreur sauvegarderTabJeu(TableauJeu* tabJeu, char nomFichier[]);
```
Ces fonctions manipulent les fichiers pour sauvegarder et charger un TableauJeu.

###### Initialisation
```C
void UTILE_InitNbJeuDispo(ListeEmprunt liste_Emprunt, TableauJeu* tabJeu);
```
Cette fonction n'est pas une fonction de TableauJeu.h mais une fonction de Ludotheque.h.
Elle initialise les nombres d'exemplaires disponibles des différents jeux.

###### Affichage

```C
void afficheTabJeu(TableauJeu* tabJeu, FILE* flux);
void affichePartieTabJeu(TableauJeu* tabJeu, unsigned int begin, unsigned int end, FILE* flux);
```
Ecrit tout ou partie d'un tableau de jeu dans un flux.

###### Recherche
```C
CodeErreur rechercherJeuInteractif(TableauJeu* tabJeu, Bool* trouve, unsigned int* rang);
unsigned int rechercherJeu(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve, Bool cherchePremier);
unsigned int _rechercherPremierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherDernierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherPremierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherDernierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
```
Permettent la recherche de jeu dans un tableau.
Les fonctions débutants par _ sont uniquement présentes pour servir `rechercherJeu`et `rechercherJeuInteractif`.

###### Tri
```C
void triTabJeuInteractif(TableauJeu* tabJeu);
void triTabJeu(TableauJeu* tabJeu, ElementJeu elementJeu);
//les fonctions suivantes sont utilisé en interne par triTabJeu
void _triJeu(Jeu* tSource[], unsigned int nbElem, ElementJeu elementJeu);
void copyTabJeu(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[]);
void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, ElementJeu elementJeu,
    Jeu* tDest[]);
```
`triTabJeuInteractif` et `triTabJeu` sont des fonctions fesant l'interface entre les fontions utilisant le tri et `_triJeu`, une fontion de tri par dichotomie.

###### Ajout et délétion
```C
CodeErreur retirerJeu(TableauJeu* tabJeu, Jeu* jeu);
CodeErreur retirerJeuInteractif(TableauJeu* tabJeu);

CodeErreur ajouterJeu(TableauJeu* tabJeu, Jeu* jeu);
CodeErreur ajouterJeuInteractif(TableauJeu* tabJeu);
//les fonctions suivantes sont utilisé en interne par retirerJeu et ajouterJeu
void _decalageAGaucheJeu(TableauJeu* tabJeu, unsigned int debut);
void _decalageADroiteJeu(TableauJeu* tabJeu, unsigned int debut);
```
Ces fonctions permettent d'ajouter ou de retirer des Jeu du tableau avec ou sans interaction avec l'utilisateur.
`retirerJeuInteractif` n'est pas utilisé dans ce projet car il est necessaire de faire des tests sur les listes de reservations et d'emprunts.
