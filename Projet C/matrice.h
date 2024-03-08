#ifndef MATRICE_H
#define MATRICE_H

// Structure matrice
typedef struct {
    int** data; // Pointeur sur la valeur de la matrice
    int ligne; // Nb of rows in the matrix
    int cols;   // Nb of columns in the matrix
} tMatrice;

// Allocate memory for a matrix and initialize its attributes
extern tMatrice* MatAllouer(int rows, int cols);

// Create a copy of a matrix
extern tMatrice* MatCopier(const tMatrice* matrix);

// Free the memory allocated for the matrix
extern void MatLiberer(tMatrice* matrix);

// Read a value from a specific position in the matrix
extern int MatLire(const tMatrice* matrix, int row, int col);

// Display the matrix
extern void MatAfficher(const tMatrice* matrix);

// Write a value to a specific position in the matrix
extern void MatEcrire(tMatrice *mat, int ligne, int colonne, unsigned char valeur);


#endif  // MATRICE_H