#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

tMatrice* MatAllouer(int ligne, int cols) {
    // Allocation
    tMatrice* matrice = malloc(sizeof(tMatrice));
    // Initialisation
    // Set the number of rows and columns in the tMatrice structure
    matrice->ligne = ligne;
    matrice->cols = cols;
    // Allocate memory for the data array (rows) of the tMatrice structure
    matrice->data = malloc(ligne * sizeof(int*));

    // Allocate memory for each column in the data array
    for (int i = 0; i < ligne; i++) {
        matrice->data[i] = malloc(cols * sizeof(int));
    }

    return matrice;
}

tMatrice* MatCopier(const tMatrice* matrice) {

    // Allocate memory for the copy tMatrice structure
    tMatrice* copy = MatAllouer(matrice->ligne, matrice->cols);

    // Copy the values from the original matrix to the copy matrix
    for (int i = 0; i < matrice->ligne; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            copy->data[i][j] = matrice->data[i][j];
        }
    }

    return copy;
}

void MatEcrire(tMatrice *mat, int ligne, int colonne, unsigned char valeur) {
    // error message if mat is empty
    if (mat == NULL) {
        fprintf(stderr, "Erreur : matrice non valide\n");
        return;
    }
    // write val in mat
    mat->data[ligne][colonne] = valeur;
}

void MatLiberer(tMatrice* matrice) {
    // Free the memory allocated for each row in mat
    for (int i = 0; i < matrice->ligne; i++) {
        free(matrice->data[i]);
    }
    // Free the memory allocated for the data tab
    free(matrice->data);
    // Free the memory allocated for the tMatrice structure
    free(matrice);
}

int MatLire(const tMatrice* matrice, int ligne, int col) {
    // Read data at ligne,colonne
    return matrice->data[ligne][col];
}


void MatAfficher(const tMatrice* matrice) {
    // Loop mat and print data
    for (int i = 0; i < matrice->ligne; i++) {
        for (int j = 0; j < matrice->cols; j++) {
            printf("%d ", matrice->data[i][j]);
        }
        printf("\n");
    }
}
