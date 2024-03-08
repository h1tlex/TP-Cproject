#include <stdio.h>
#include <stdlib.h>
#include "polygone.h"

typedef struct sPolygone * tPolygone ;

int main(int argc, char const *argv[])
{
    int x=0;
    int y=0;

    tPolygone Poly = PolygoneCreer();

    while(y<=10 && x<=10)
    {
        PolygoneAjouterSommetEnFin(x,y,Poly);
        x++;
        y++;
    }
    
    x= 153;
    y=124;
    while(y<=424 && x<=642)
    {
        PolygoneAjouterSommetEnFin(x,y,Poly);
        x++;
        y++;
    }
    PolygoneAjouterSommetEnIeme(4,5,34,Poly);
    PolygoneSommetSupprimerIeme(2,Poly);
    PolygoneSommetIeme(Poly,3,&x,&y);
    PolygoneNbSommets(Poly);
    PolygoneAfficher(Poly);

    FILE *f = fopen("Poly.txt", "w");
    PolygoneEcriref(Poly, f);  // write polygon to file
    fclose(f);

    
    FILE* IdFichSVG = SvgCreer("IdFichSVG.svg", 100, 100); // Create file and open it
    tStyle Style={"blue",5,1,"none",0,"red",1}; // Random testing style

    PolygoneEcrireSvg(Poly, &Style, IdFichSVG); // Call the PolygoneEcrireSvg function
    fclose(IdFichSVG);     // Close the SVG file

    return 0;
}

