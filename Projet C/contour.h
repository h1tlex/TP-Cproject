#ifndef CONTOUR_H
#define CONTOUR_H

#include "image.h"
#include "polygone.h"

// Function to extract labels from an image of labels
extern int ContourEtiquettes(char NomFichEtiquettes[], unsigned char *Etiquettes);

// Function to track the contour of a region
extern tPolygone ContourSuivi(tImage Im, unsigned char Etiquette);

// Function to extract contours of regions and write their coordinates to a file
extern void ContourExtraire(char NomFichEtiquettes[], unsigned char Etiquette[], int NbRegions, char NomFichContours[]);


// Function to write contours on an SVG image
void ContourEcrireSurImageSvg(char NomFichContours[], char NomFichImage[], int NbCol, int NbLig, tStyle *pStyle, char NomFichSVG[]);

#endif /* CONTOUR_H */