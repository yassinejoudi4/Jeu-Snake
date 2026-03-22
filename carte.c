#include "carte.h"
#include <stdlib.h>

Carte* creer_carte(int taille) {
    Carte* carte = (Carte*)malloc(sizeof(Carte));
    carte->taille = taille;
    carte->grille = (int**)malloc(sizeof(int*) * taille);
    for (int i = 0; i < taille; i++) {
        carte->grille[i] = (int*)malloc(sizeof(int) * taille);
        for (int j = 0; j < taille; j++) carte->grille[i][j] = VIDE;
    }
    return carte;
}

void liberer_carte(Carte* carte) {
    for (int i = 0; i < carte->taille; i++) free(carte->grille[i]);
    free(carte->grille);
    free(carte);
}

void placer_murs_bords(Carte* carte) {
    for (int i = 0; i < carte->taille; i++) {
        carte->grille[i][0] = MUR;
        carte->grille[i][carte->taille-1] = MUR;
        carte->grille[0][i] = MUR;
        carte->grille[carte->taille-1][i] = MUR;
    }
}

void placer_fruit_aleatoire(Carte* carte) {
    int x = rand() % (carte->taille - 2) + 1;
    int y = rand() % (carte->taille - 2) + 1;
    while (carte->grille[x][y] != VIDE) {
        x = rand() % (carte->taille - 2) + 1;
        y = rand() % (carte->taille - 2) + 1;
    }
    carte->grille[x][y] = FRUIT;
}

int est_position_valide(Carte* carte, Position pos) {
    return pos.x >= 0 && pos.x < carte->taille && pos.y >= 0 && pos.y < carte->taille;
}

void afficher_carte_graphique(Carte* carte, SDL_Renderer* renderer) {
    SDL_Color couleur_mur = {50, 50, 50, 255};
    SDL_Color couleur_fruit = {255, 0, 0, 255};

    for (int i = 0; i < carte->taille; i++) {
        for (int j = 0; j < carte->taille; j++) {
            SDL_Rect rect = {j * TAILLE_CASE, i * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE};
            if (carte->grille[i][j] == MUR) {
                SDL_SetRenderDrawColor(renderer, couleur_mur.r, couleur_mur.g, couleur_mur.b, couleur_mur.a);
                SDL_RenderFillRect(renderer, &rect);
            } else if (carte->grille[i][j] == FRUIT) {
                SDL_SetRenderDrawColor(renderer, couleur_fruit.r, couleur_fruit.g, couleur_fruit.b, couleur_fruit.a);
                int cx = j*TAILLE_CASE + TAILLE_CASE/2;
                int cy = i*TAILLE_CASE + TAILLE_CASE/2;
                int r = TAILLE_CASE/2 - 2;
                for (int w = -r; w <= r; w++) {
                    for (int h = -r; h <= r; h++) {
                        if (w*w + h*h <= r*r) SDL_RenderDrawPoint(renderer, cx+w, cy+h);
                    }
                }
            }
        }
    }
}

