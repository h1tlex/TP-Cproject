#ifndef POLYGONE_H
#define POLYGONE_H
#include "svg.h"

// Type permettant de manipuler un polygone
typedef struct sPolygone * tPolygone ;




// Fonction qui cree un polygone vide
extern tPolygone PolygoneCreer(void);


// retourne le nombre de sommets de Poly
extern int PolygoneNbSommets(tPolygone Poly);


// ajoute un sommet de coordonnées (x,y) à la fin de Poly 
extern void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly);

// ajoute un sommet de coordonnées (x,y) au début de Poly ;
extern void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly);

// ajouter un polygone à une Ieme position
extern void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly);

// affiche les coordonées d'un polygone
extern void PolygoneAfficher(tPolygone Poly);
// trouve les coordonnées specifique d'un point dans le polygone
extern void PolygoneSommetIeme(tPolygone Poly, int i, int *px, int *py);

// supprimer un point dans un polygone
extern void PolygoneSommetSupprimerIeme(int i, tPolygone Poly);

// libere la memoire occuper par tout les sommets d'un polygone
extern void PolygoneLiberer(tPolygone Poly);
// lire les coordonees d'un polygone d'un fichier txt et le crée
extern tPolygone PolygoneLiref(FILE *f);

// ecrire les coordonees d'un polygone d'un fichier txt 
extern void PolygoneEcriref(tPolygone Poly, FILE *f);


extern void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG);

#endif //POLYGONE_H