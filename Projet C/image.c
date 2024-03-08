#include "image.h"
#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


struct sImage {
    int NbLig;
    int NbCol;
    tMatrice* NivGris;
};

tImage ImAllouer(int NbLignes, int NbColonnes) {
    // Allocate memory for the image structure
    tImage image = malloc(sizeof(struct sImage));
    // Set the number of rows and columns of the image
    image->NbLig = NbLignes;
    image->NbCol = NbColonnes;
    // Allocate memory for the grayscale matrix of the image
    image->NivGris = MatAllouer(NbLignes, NbColonnes);
    return image;
}

void ImLiberer(tImage *pIm) {
    // Check if the image pointer is not NULL
    if (*pIm != NULL) {
        // Deallocate memory for the grayscale matrix
        MatLiberer((*pIm)->NivGris);
        // Free the image structure
        free(*pIm);
        // Set the image pointer to NULL
        *pIm = NULL;
    }
}

int ImNbLig(tImage Im) {
    return Im->NbLig;
}

int ImNbCol(tImage Im) {
    return Im->NbCol;
}

// Convert an image to a grayscale matrix
tMatrice* ImNivGris(tImage Im) {
    return Im->NivGris;
}

tImage ImLire(char NomFichier[]) {
    FILE *file = fopen(NomFichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Lire la signature
    char signature[3];
    fscanf(file, "%2s", signature);
    if (strcmp(signature, "P2") != 0) {
        printf("Format de fichier invalide.\n");
        fclose(file);
        return NULL;
    }

    // Lire les dimensions
    int nbCols, nbLignes;
    fscanf(file, "%d%d", &nbCols, &nbLignes);

    // Lire le niveau de gris maximal
    int niveauMax;
    fscanf(file, "%d", &niveauMax);

    // Allouer l'image
    tImage image = ImAllouer(nbLignes, nbCols);

    // Lire les niveaux de gris
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbCols; j++) {
            int niveau;
            fscanf(file, "%d", &niveau);
            int niveauTransforme = round(255.0 * niveau / niveauMax);
            MatEcrire(image->NivGris, i, j, niveauTransforme); //maybe change to matAllouer
        }
    }

    fclose(file);
    return image;
}

void ImEcrire(tImage Im, char NomFichier[]) {
    FILE *file = fopen(NomFichier, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Écrire la signature
    fprintf(file, "P2\n");

    // Écrire les dimensions
    fprintf(file, "%d %d\n", ImNbCol(Im), ImNbLig(Im));

    // Écrire le niveau de gris maximal
    fprintf(file, "255\n");

    // Écrire les niveaux de gris
    for (int i = 0; i < ImNbLig(Im); i++) {
        for (int j = 0; j < ImNbCol(Im); j++) {
            int niveau = round(MatLire(Im->NivGris, i, j));
            fprintf(file, "%d ", niveau);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}