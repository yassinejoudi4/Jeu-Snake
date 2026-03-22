#ifndef CARTE_H
#define CARTE_H

#include <SDL2/SDL.h>

#define TAILLE_CARTE 20
#define TAILLE_CASE 30

typedef enum {
    VIDE = 0,
    MUR = 1,
    FRUIT = 2
} TypeCase;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int** grille;
    int taille;
} Carte;

// Fonctions
Carte* creer_carte(int taille);
void liberer_carte(Carte* carte);

void placer_murs_bords(Carte* carte);
void placer_fruit_aleatoire(Carte* carte);

int est_position_valide(Carte* carte, Position pos);
int est_position_libre(Carte* carte, Position pos);

void afficher_carte_console(Carte* carte);
void afficher_carte_graphique(Carte* carte, SDL_Renderer* renderer);

#endif

