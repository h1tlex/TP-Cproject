#ifndef IMAGE_H
#define IMAGE_H

#include "matrice.h"

// declaration de struct image
typedef struct sImage *tImage;

// Allocate memory for a new image
extern tImage ImAllouer(int NbLignes, int NbColonnes);

// Deallocate memory for an image
extern void ImLiberer(tImage *pIm);

// Get the number of rows in an image
extern int ImNbLig(tImage Im);

// Get the number of columns in an image
extern int ImNbCol(tImage Im);

// Convert an image to a grayscale matrix
extern tMatrice* ImNivGris(tImage Im);

// Read an image from a file
extern tImage ImLire(char NomFichier[]);

// Write an image to a file
extern void ImEcrire(tImage Im, char NomFichier[]);


#endif  // IMAGE_H