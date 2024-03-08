#include <stdio.h>
#include <stdlib.h>
#include "contour.h"

//main test
int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./contex <NomFichEtiquettes> <NomFichImage> <NomFichContours> <NomFichSVG>\n");
        return 1;
    }
    // arguments
    char* NomFichEtiquettes = argv[1];
    char* NomFichImage = argv[2];
    char* NomFichContours = argv[3];
    char* NomFichSVG = argv[4];

    unsigned char Etiquette[2]; // Nombre d'étiquettes des régions à extraire 

    // Extraction des étiquettes des régions
    int NbRegions = ContourEtiquettes(NomFichEtiquettes, Etiquette);
    printf("Nombre d'etiquettes trouvees : %d\n", NbRegions);

    // Extraction des contours des régions
    // ContourExtraire(NomFichEtiquettes, Etiquette, NbRegions, NomFichContours);
    // printf("Contours extraits et ecrits dans le fichier : %s\n", NomFichContours);

    // Écriture des contours sur l'image SVG
    // int NbCol = 0; // Spécifiez le nombre de colonnes de l'image
    // int NbLig = 0; // Spécifiez le nombre de lignes de l'image
    // tStyle* pStyle = NULL; // Spécifiez le style des contours
    // ContourEcrireSurImageSvg(NomFichContours, NomFichImage, NbCol, NbLig, pStyle, NomFichSVG);
    // printf("Contours ecrits sur l'image SVG dans le fichier : %s\n", NomFichSVG);

    return 0;
}