#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGEUR 14
#define HAUTEUR 10

typedef struct {
    int x;
    int y;
} Position;

void initialiserGrille(char grille[HAUTEUR][LARGEUR]);
void afficherGrille(char grille[HAUTEUR][LARGEUR]);
int deplacerJoueur(char grille[HAUTEUR][LARGEUR], Position *joueur, int dx, int dy);
int deplacerCaisse(char grille[HAUTEUR][LARGEUR], Position *caisse, int dx, int dy);
int estGagnant(char grille[HAUTEUR][LARGEUR], Position caisse);
int estPerdu(char grille[HAUTEUR][LARGEUR], Position caisse);

#endif // et end de l'exo <3
