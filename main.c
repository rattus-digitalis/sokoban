#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void initialiserGrille(char grille[HAUTEUR][LARGEUR]) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (i == 0 || i == HAUTEUR - 1 || j == 0 || j == LARGEUR - 1) {
                grille[i][j] = '#';
            } else {
                grille[i][j] = ' ';
            }
        }
    }
    grille[HAUTEUR - 2][LARGEUR - 2] = '*';
    grille[1][1] = 'o';
    grille[HAUTEUR - 3][LARGEUR - 3] = 'X';
}

void afficherGrille(char grille[HAUTEUR][LARGEUR]) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
}

int deplacerJoueur(char grille[HAUTEUR][LARGEUR], Position *joueur, int dx, int dy) {
    int nouvelleX = joueur->x + dx;
    int nouvelleY = joueur->y + dy;

    if (grille[nouvelleY][nouvelleX] == ' ' || grille[nouvelleY][nouvelleX] == '*') {
        grille[joueur->y][joueur->x] = ' ';
        joueur->x = nouvelleX;
        joueur->y = nouvelleY;
        grille[joueur->y][joueur->x] = 'o';
        return 1;
    } else if (grille[nouvelleY][nouvelleX] == 'X') {
        if (deplacerCaisse(grille, &(Position){nouvelleX, nouvelleY}, dx, dy)) {
            grille[joueur->y][joueur->x] = ' ';
            joueur->x = nouvelleX;
            joueur->y = nouvelleY;
            grille[joueur->y][joueur->x] = 'o';
            return 1;
        }
    }
    return 0;
}

int deplacerCaisse(char grille[HAUTEUR][LARGEUR], Position *caisse, int dx, int dy) {
    int nouvelleX = caisse->x + dx;
    int nouvelleY = caisse->y + dy;

    if (grille[nouvelleY][nouvelleX] == ' ' || grille[nouvelleY][nouvelleX] == '*') {
        grille[caisse->y][caisse->x] = ' ';
        caisse->x = nouvelleX;
        caisse->y = nouvelleY;
        grille[caisse->y][caisse->x] = 'X';
        return 1;
    }
    return 0;
}

int estGagnant(char grille[HAUTEUR][LARGEUR], Position caisse) {
    return grille[caisse.y][caisse.x] == '*';
}

int estPerdu(char grille[HAUTEUR][LARGEUR], Position caisse) {
    return (grille[caisse.y + 1][caisse.x] == '#' && grille[caisse.y][caisse.x + 1] == '#') ||
           (grille[caisse.y - 1][caisse.x] == '#' && grille[caisse.y][caisse.x - 1] == '#');
}

int main() {
    char grille[HAUTEUR][LARGEUR];
    Position joueur = {1, 1};
    Position caisse = {LARGEUR - 3, HAUTEUR - 3};
    char mouvement;

    srand(time(NULL));
    initialiserGrille(grille);

    printf("\n");
    printf("Joueur : 'o'\n");
    printf("Caisse : 'X'\n");
    printf("Objectif : '*'\n\n");

    while (1) {
        afficherGrille(grille);
        if (estGagnant(grille, caisse)) {
            printf("Vous avez gagné !\n");
            break;
        }
        if (estPerdu(grille, caisse)) {
            printf("Vous avez perdu !\n");
            break;
        }

        printf("\nEntrez votre mouvement (z: haut, s: bas, q: gauche, d: droite): ");
        scanf(" %c", &mouvement);

        int deplacementEffectue = 0;

        switch (mouvement) {
            case 'z':
                deplacementEffectue = deplacerJoueur(grille, &joueur, 0, -1);
                break;
            case 's':
                deplacementEffectue = deplacerJoueur(grille, &joueur, 0, 1);
                break;
            case 'q':
                deplacementEffectue = deplacerJoueur(grille, &joueur, -1, 0);
                break;
            case 'd':
                deplacementEffectue = deplacerJoueur(grille, &joueur, 1, 0);
                break;
            default:
                printf("Mouvement invalide.\n");
                continue;
        }

        if (!deplacementEffectue) {
            printf("Impossible de déplacer !\n");
        }
    }

    return 0;
}
