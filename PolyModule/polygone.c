#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "polygone.h"





// Sommet d’un polygone
struct sSommet{

    int x , y ; // Coordonnées entières du sommet
    struct sSommet * pSuivant ; // Adresse du sommet suivant
};

// Descripteur du polygone pointant vers une liste simplement chaînée de sommets
struct sPolygone{

    int NbSommets ; // Nombre de sommets
    struct sSommet * PremierSommet ; // Adresse du premier sommet
};






// Fonction qui cree un polygone vide
tPolygone PolygoneCreer(void){

    tPolygone polygone = malloc(sizeof(struct sPolygone));

    polygone->NbSommets = 0;
    polygone->PremierSommet = NULL;
    return polygone;
}


// retourne le nombre de sommets de Poly
int PolygoneNbSommets(tPolygone Poly){

    return Poly->NbSommets;
}



// ajoute un sommet de coordonnées (x,y) à la fin de Poly 
void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly){

    struct sSommet* nouveau_sommet = malloc(sizeof(struct sSommet)); // Creation du nouveau sommet

    // coordonner du nouveau sommet
    nouveau_sommet->x = x;
    nouveau_sommet->y = y;
    nouveau_sommet->pSuivant = NULL; // NULL car dernier sommet

    // Ajouter le nouveau sommet comme premier sommet si le polygone n'a pas de premier sommet
    if (Poly->PremierSommet == NULL) {
        Poly->PremierSommet = nouveau_sommet;
    }
    else { // si le polygone a déjà un sommet, trouver le dernier sommet et allouer son pSuivant comme nouveau sommet
        struct sSommet* dernier_sommet = Poly->PremierSommet; // cree le dernier sommet
        while (dernier_sommet->pSuivant != NULL) { // si on est pas sur le dernier sommet
            dernier_sommet = dernier_sommet->pSuivant; // passer au sommet suivant
        }
        dernier_sommet->pSuivant = nouveau_sommet; // sortie de la boucle alors on est sur le dernier sommet, allouer le nouveau sommet
    }

    Poly->NbSommets++;
}

// ajoute un sommet de coordonnées (x,y) au début de Poly ;
void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly){

    struct sSommet* nouveau_sommet = malloc(sizeof(struct sSommet)); // Creation du nouveau sommet

    // coordonner du nouveau sommet
    nouveau_sommet->x = x;
    nouveau_sommet->y = y;
    nouveau_sommet->pSuivant = Poly->PremierSommet; // pSuivant est Premier sommet car le nouveau sommet est au debut

    Poly->PremierSommet = nouveau_sommet; // allocation du nouveau sommet comme premier sommet

    Poly->NbSommets++;
}

// ajouter un polygone à une Ieme position
void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly){

    // ajouter en début
    if (i == 0) {
        PolygoneAjouterSommetEnDebut(x, y, Poly);
        return;
    }

    // ajouter à la fin
    if (i == Poly->NbSommets) {
        PolygoneAjouterSommetEnFin(x, y, Poly);
        return;
    }
    
    // ajouter en Ieme position

    struct sSommet* previousSommet = NULL; // sommet precedent
    struct sSommet* currentSommet = Poly->PremierSommet; // sommet actuel
    int j = 0;

    // parcours de la liste chainée des sommets
    while (j < i) {
        previousSommet = currentSommet;
        currentSommet = currentSommet->pSuivant;
        j++;
        // on s'arret à la Ieme postion
    }

    struct sSommet* nouveau_sommet = malloc(sizeof(struct sSommet)); // cree le sommet à ajouter



    // allouer le sommet
    nouveau_sommet->x = x;
    nouveau_sommet->y = y;
    nouveau_sommet->pSuivant = currentSommet; // on link le sommet de la Ieme position comme sommet suivant
    previousSommet->pSuivant = nouveau_sommet; // on link le sommet precedent avec le nouveau sommet

    Poly->NbSommets++;
}

// affiche les coordonées d'un polygone
void PolygoneAfficher(tPolygone Poly) {

    // nombre de sommet
    int n = Poly->NbSommets;
    printf("%d\n", n);
    
    struct sSommet* pSommet = Poly->PremierSommet;

    // Traverse la liste chainée et print chaque coordonnée
    while (pSommet != NULL) {
        printf("%d %d\n", pSommet->x, pSommet->y);
        pSommet = pSommet->pSuivant;
    }
}

// trouve les coordonnées specifique d'un point dans le polygone
void PolygoneSommetIeme(tPolygone Poly, int i, int *px, int *py) {


    struct sSommet* pSommet = Poly->PremierSommet;

    // traverser la liste chainnée pour arriver au point
    for (int j = 0; j < i; j++) {
        pSommet = pSommet->pSuivant;
    }
    
    // allouer les coordonnées du point au pointeurs
    *px = pSommet->x;
    *py = pSommet->y;
}

// supprimer un point dans un polygone
void PolygoneSommetSupprimerIeme(int i, tPolygone Poly) {

    if (Poly == NULL || Poly->NbSommets <= i) {
        // input invalide
        return;
    }
    
    // traverser la liste chainnée pour arriver au point
    struct sSommet* currentSommet = Poly->PremierSommet;
    struct sSommet* previousSommet = NULL;
    int compteur = 0;

    while (currentSommet != NULL && compteur < i) { // tant que on est pas sur le dernier sommet et le compteur inferieur à l'index
        previousSommet = currentSommet;
        currentSommet = currentSommet->pSuivant;
        compteur++;
        // on avance dans la liste
    }
    
    if (currentSommet != NULL) { // si vide alors rien a supprimer
        // supprimer le Ieme point
        if (previousSommet != NULL) {  // si pas vide alors on est pas sur le premier sommet
            previousSommet->pSuivant = currentSommet->pSuivant; // update et skip le sommet à supprimer
        } else { // on est sur le premier sommet
            Poly->PremierSommet = currentSommet->pSuivant; // on supprime le premier sommet
        }
        free(currentSommet); // on suprime l'allocation de memoire
        Poly->NbSommets--;
    }
}

// libere la memoire occuper par tout les sommets d'un polygone
void PolygoneLiberer(tPolygone Poly) {
    
    struct sSommet* currentSommet = Poly->PremierSommet;
    // parcours des sommets et free chaqu'un
    while (currentSommet != NULL) {
        struct sSommet* nextSommet = currentSommet->pSuivant;
        free(currentSommet);
        currentSommet = nextSommet;
    }

    // Free the memory occupied by the polygon itself
    free(Poly);
}

// lire les coordonees d'un polygone d'un fichier txt et le crée
tPolygone PolygoneLiref(FILE *f) {

    int n;
    fscanf(f, "%d", &n);  // lire le nbSommet

    tPolygone Poly = PolygoneCreer();  // cree un polygone vide
    int x, y;

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %d", &x, &y);  // lire les coordonnees x et y
        PolygoneAjouterSommetEnFin(x, y, Poly);  // ajouter le sommet au polygone
    }

    return Poly;
}

// ecrire les coordonees d'un polygone d'un fichier txt 
void PolygoneEcriref(tPolygone Poly, FILE *f) {

    // ecrit nbSommets du polygone dans f
    fprintf(f, "%d\n", Poly->NbSommets); 
    
    // ecrit les coordonées de chaque sommet
    struct sSommet* currentSommet = Poly->PremierSommet;
    while (currentSommet != NULL) {
        fprintf(f, "%d %d\n", currentSommet->x, currentSommet->y);
        currentSommet = currentSommet->pSuivant;
    }
    
    
}


//ecrire polygone dans un fichier svg
void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG) {

    struct sSommet* currentSommet = Poly->PremierSommet;
    int NbSommets=PolygoneNbSommets(Poly);
    float xTab[NbSommets];
    float yTab[NbSommets];

    
    for (int i = 0; i < NbSommets; i++){
        xTab[i]=currentSommet->x;
        yTab[i]=currentSommet->y;
        // passer au sommet suivant
        currentSommet = currentSommet->pSuivant;
        i++;
    }

    SvgEcrirePolygone(IdFichSVG, xTab, yTab, NbSommets, pStyle); // appel de la fonction du fichier svg.c
}

