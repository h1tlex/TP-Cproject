#include "contour.h"
#include "polygone.h"
#include "image.h"
#include "svg.h"

#include <stdlib.h>

int ContourEtiquettes(char NomFichEtiquettes[], unsigned char Etiquettes[]) {
    // Read the image of labels from the file
    tImage etiquettes = ImLire(NomFichEtiquettes);

    int nbEtiquettes = 0;  // Number of unique labels found
    int nbLignes = ImNbLig(etiquettes);
    int nbColonnes = ImNbCol(etiquettes);
    tMatrice* matEtiquettes = ImNivGris(etiquettes);  // Grayscale matrix of labels

    // Iterate over the image and extract unique labels
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbColonnes; j++) {
            unsigned char etiquette = MatLire(matEtiquettes, i, j);

            // Check if the label is non-zero (valid label)
            if (etiquette != 0) {
                int found = 0;  // Flag to check if the label is already found

                // Iterate over existing unique labels to check for duplicates
                for (int k = 0; k < nbEtiquettes; k++) {
                    if (Etiquettes[k] == etiquette) {
                        found = 1;
                        break;
                    }
                }

                // If the label is not a duplicate, add it to the unique labels tab
                if (!found) {
                    Etiquettes[nbEtiquettes] = etiquette;
                    nbEtiquettes++;
                }
            }
        }
    }

    ImLiberer(&etiquettes);  // Free the memory allocated for the image

    return nbEtiquettes;
}

tPolygone ContourSuivi(tImage Im, unsigned char Etiquette) {
    int nbLignes = ImNbLig(Im);
    int nbColonnes = ImNbCol(Im);
    tMatrice* matEtiquettes = ImNivGris(Im);

    int startX = -1;
    int startY = -1;

    // Trouver le point de départ du contour
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbColonnes; j++) {
            if (MatLire(matEtiquettes, i, j) == Etiquette) {
                startX = j;
                startY = i;
                break;
            }
        }
        if (startX != -1 && startY != -1) {
            break;
        }
    }

    if (startX == -1 || startY == -1) {
        printf("Erreur : étiquette introuvable.\n");
        tPolygone polygoneVide = PolygoneCreer();
        return polygoneVide;
    }

    tPolygone polygone = PolygoneCreer();
    int currentX = startX;
    int currentY = startY;
    int direction = 0; // 0: droite, 1: bas, 2: gauche, 3: haut

    do {
        PolygoneAjouterSommetEnFin(currentX, currentY, polygone);
        // Déterminer la prochaine direction
        int found = 0;

        for (int i = 0; i < 4; i++){

            int nextX = currentX;
        int nextY = currentY;
        if (direction == 0) {
            nextX++;
        } else if (direction == 1) {
            nextY++;
        } else if (direction == 2) {
            nextX--;
        } else if (direction == 3) {
            nextY--;
        }
        // Vérifier si le prochain pixel est dans la région
        if (nextX >= 0 && nextX < nbColonnes && nextY >= 0 && nextY < nbLignes && MatLire(matEtiquettes, nextY, nextX) == Etiquette) {
            found = 1;
            currentX = nextX;
            currentY = nextY;
            break;
        }
        // Changer de direction
        direction = (direction + 1) % 4;
        }

    if (!found) {
        printf("Erreur : contour incomplet.\n");
        PolygoneLiberer(polygone);
        tPolygone polygoneVide = PolygoneCreer();
        return polygoneVide;}

    } 
    while (currentX != startX || currentY != startY);

    return polygone;        
    }

void ContourExtraire(char NomFichEtiquettes[], unsigned char Etiquette[], int NbRegions, char NomFichContours[]) {
    FILE* fichierContours = fopen(NomFichContours, "w");
    if (fichierContours == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des contours.\n");
        return;
    }

    // Récupérer les étiquettes des régions de l'image
    unsigned char etiquettes[NbRegions];
    int nbEtiquettes = ContourEtiquettes(NomFichEtiquettes, etiquettes);

    // Vérifier si toutes les étiquettes spécifiées existent dans l'image
    for (int i = 0; i < NbRegions; i++) {
        int found = 0;
        for (int j = 0; j < nbEtiquettes; j++) {
            if (etiquettes[j] == Etiquette[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Erreur : L'etiquette %d n'existe pas dans l'image.\n", Etiquette[i]);
            fclose(fichierContours);
            return;
        }
    }

    tImage image = ImLire(NomFichEtiquettes);
    if (image == NULL) {
        printf("Erreur : Impossible de lire l'image d'etiquettes.\n");
        fclose(fichierContours);
        return;
    }

    // Parcourir les régions spécifiées et extraire leurs contours
    for (int i = 0; i < NbRegions; i++) {
        tPolygone contour = ContourSuivi(image, Etiquette[i]);
        int nbSommets = PolygoneNbSommets(contour);

        // Écrire le nombre de sommets du contour dans le fichier
        fprintf(fichierContours, "%d\n", nbSommets);

        // Écrire les coordonnées des sommets du contour dans le fichier
        for (int j = 0; j < nbSommets; j++) {
            int x, y;
            PolygoneSommetIeme(contour,j,&x, &y);
            fprintf(fichierContours, "%d %d\n", x, y);
        }

        PolygoneLiberer(contour);
    }

    ImLiberer(&image);
    fclose(fichierContours);
}

void ContourEcrireSurImageSvg(char NomFichContours[], char NomFichImage[], int NbCol, int NbLig, tStyle *pStyle, char NomFichSVG[]) {
    // Read the contours from the file
    FILE* fichierContours = fopen(NomFichContours, "r");
    if (fichierContours == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier des contours.\n");
        return;
    }

    // Create a polygon for each contour
    tPolygone* contours = (tPolygone*)malloc(sizeof(tPolygone));
    int nbContours = 0;
    int nbSommets;
    fscanf(fichierContours, "%d", &nbContours);
    for (int i = 0; i < nbContours; i++) {
        fscanf(fichierContours, "%d", &nbSommets);
        tPolygone polygone = PolygoneCreer();
        for (int j = 0; j < nbSommets; j++) {
            int x, y;
            fscanf(fichierContours, "%d%d", &x, &y);
            PolygoneAjouterSommetEnFin(x, y, polygone);
        }
        contours[i] = polygone;
    }
    fclose(fichierContours);

    // Load the PNG image
    tImage image = ImLire(NomFichImage);
    if (image == NULL) {
        printf("Erreur : Impossible de charger l'image PNG.\n");
        for (int i = 0; i < nbContours; i++) {
            PolygoneLiberer(contours[i]);
        }
        free(contours);
        return;
    }

    // Create an SVG file and draw the contours
    FILE* fichierSVG = fopen(NomFichSVG, "w");
    if (fichierSVG == NULL) {
        printf("Erreur : Impossible de créer le fichier SVG.\n");
        for (int i = 0; i < nbContours; i++) {
            PolygoneLiberer(contours[i]);
        }
        free(contours);
        ImLiberer(&image);
        return;
    }

    fichierSVG = SvgCreer(NomFichSVG, NbCol, NbLig);
    for (int i = 0; i < nbContours; i++) {
        PolygoneEcrireSvg(contours[i], pStyle, fichierSVG);
    }
    SvgFermer(fichierSVG);

    fclose(fichierSVG);
    for (int i = 0; i < nbContours; i++) {
        PolygoneLiberer(contours[i]);
    }
    free(contours);
    ImLiberer(&image);
}