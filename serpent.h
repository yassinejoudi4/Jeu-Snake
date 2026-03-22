#ifndef SERPENT_H
#define SERPENT_H

#include "carte.h"
#include <SDL2/SDL.h>

typedef enum { HAUT, BAS, GAUCHE, DROITE } Direction;

typedef struct Unite {
    Position position;
    struct Unite* suivant;
    struct Unite* precedent;
} Unite;

typedef struct {
    Unite* tete;
    Unite* queue;
    Direction direction;
    int longueur;
    int croissance;
} Serpent;

Serpent* creer_serpent(Position position_initiale, Direction direction_initiale);
void liberer_serpent(Serpent* serpent);
void deplacer_serpent(Serpent* serpent);
void changer_direction(Serpent* serpent, Direction nouvelle_direction);
void faire_manger_serpent(Serpent* serpent);
int verifier_collision_murs(Serpent* serpent, Carte* carte);
int verifier_auto_collision(Serpent* serpent);
Position obtenir_prochaine_position(Serpent* serpent);
int est_position_sur_serpent(Serpent* serpent, Position pos);
void afficher_serpent_graphique(Serpent* serpent, SDL_Renderer* renderer);

#endif

