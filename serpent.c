#include "serpent.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

Serpent* creer_serpent(Position position_initiale, Direction direction_initiale) {
    Serpent* serpent = (Serpent*)malloc(sizeof(Serpent));
    Unite* tete = (Unite*)malloc(sizeof(Unite));
    tete->position = position_initiale;
    tete->suivant = tete->precedent = NULL;
    serpent->tete = serpent->queue = tete;
    serpent->direction = direction_initiale;
    serpent->longueur = 1;
    serpent->croissance = 0;
    return serpent;
}

void liberer_serpent(Serpent* serpent) {
    Unite* u = serpent->tete;
    while (u) {
        Unite* tmp = u->suivant;
        free(u);
        u = tmp;
    }
    free(serpent);
}

Position obtenir_prochaine_position(Serpent* serpent) {
    Position p = serpent->tete->position;
    switch(serpent->direction) {
        case HAUT: p.x--; break;
        case BAS: p.x++; break;
        case GAUCHE: p.y--; break;
        case DROITE: p.y++; break;
    }
    return p;
}

void deplacer_serpent(Serpent* serpent) {
    Position next = obtenir_prochaine_position(serpent);
    Unite* nouv = (Unite*)malloc(sizeof(Unite));
    nouv->position = next;
    nouv->suivant = serpent->tete;
    nouv->precedent = NULL;
    serpent->tete->precedent = nouv;
    serpent->tete = nouv;

    if (serpent->croissance > 0) {
        serpent->croissance--;
        serpent->longueur++;
    } else {
        Unite* old_queue = serpent->queue;
        serpent->queue = serpent->queue->precedent;
        serpent->queue->suivant = NULL;
        free(old_queue);
    }
}

int directions_opposées(Direction d1, Direction d2) {
    return (d1==HAUT && d2==BAS) || (d1==BAS && d2==HAUT) || (d1==GAUCHE && d2==DROITE) || (d1==DROITE && d2==GAUCHE);
}

void changer_direction(Serpent* serpent, Direction nouvelle_direction) {
    if (!directions_opposées(serpent->direction, nouvelle_direction))
        serpent->direction = nouvelle_direction;
}

void faire_manger_serpent(Serpent* serpent) { serpent->croissance += 3; }

int verifier_collision_murs(Serpent* serpent, Carte* carte) {
    Position p = serpent->tete->position;
    return !est_position_valide(carte, p) || carte->grille[p.x][p.y]==MUR;
}

int verifier_auto_collision(Serpent* serpent) {
    Position p = serpent->tete->position;
    Unite* u = serpent->tete->suivant;
    while(u) {
        if(u->position.x==p.x && u->position.y==p.y) return 1;
        u = u->suivant;
    }
    return 0;
}

int est_position_sur_serpent(Serpent* serpent, Position pos) {
    Unite* u = serpent->tete;
    while(u) { if(u->position.x==pos.x && u->position.y==pos.y) return 1; u=u->suivant; }
    return 0;
}

void afficher_serpent_graphique(Serpent* serpent, SDL_Renderer* renderer) {
    SDL_Color couleur_corps = {255,255,0,255}; // jaune
    SDL_Color couleur_tete = {0,255,0,255};    // vert
    SDL_Color couleur_bordure = {30,30,30,255};

    Unite* u = serpent->tete;
    int n=0;
    while(u){
        SDL_Rect rect = {u->position.y*TAILLE_CASE, u->position.x*TAILLE_CASE, TAILLE_CASE, TAILLE_CASE};
        SDL_Color c = (n==0)? couleur_tete : couleur_corps;
        SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,c.a);
        SDL_RenderFillRect(renderer,&rect);

        SDL_SetRenderDrawColor(renderer,couleur_bordure.r,couleur_bordure.g,couleur_bordure.b,couleur_bordure.a);
        SDL_RenderDrawRect(renderer,&rect);
        u = u->suivant; n++;
    }
}

