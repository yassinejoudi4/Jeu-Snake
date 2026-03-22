

#include "carte.h"
#include "serpent.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    srand(42);
    if(SDL_Init(SDL_INIT_VIDEO)<0){ printf("Erreur SDL: %s\n",SDL_GetError()); return 1; }

    int windowSize = TAILLE_CARTE*TAILLE_CASE;
    SDL_Window* window = SDL_CreateWindow("Snake SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowSize,windowSize,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Carte* carte = creer_carte(TAILLE_CARTE);
    placer_murs_bords(carte);

    Position pos_init = {TAILLE_CARTE/2,TAILLE_CARTE/2};
    Serpent* serpent = creer_serpent(pos_init,DROITE);

    for(int i=0;i<5;i++) placer_fruit_aleatoire(carte);

    int running = 1, jeu_actif=1;
    SDL_Event event;
    Uint32 dernier_mouvement = SDL_GetTicks();
    const Uint32 intervalle_mouvement = 200;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) running=0;
            if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: running=0; break;
                    case SDLK_r:
                        liberer_serpent(serpent);
                        liberer_carte(carte);
                        carte = creer_carte(TAILLE_CARTE);
                        placer_murs_bords(carte);
                        serpent = creer_serpent((Position){TAILLE_CARTE/2,TAILLE_CARTE/2},DROITE);
                        for(int i=0;i<5;i++) placer_fruit_aleatoire(carte);
                        jeu_actif=1;
                        break;
                    case SDLK_UP: if(jeu_actif) changer_direction(serpent,HAUT); break;
                    case SDLK_DOWN: if(jeu_actif) changer_direction(serpent,BAS); break;
                    case SDLK_LEFT: if(jeu_actif) changer_direction(serpent,GAUCHE); break;
                    case SDLK_RIGHT: if(jeu_actif) changer_direction(serpent,DROITE); break;
                }
            }
        }

        if(jeu_actif && SDL_GetTicks()-dernier_mouvement>intervalle_mouvement){
            dernier_mouvement=SDL_GetTicks();
            deplacer_serpent(serpent);
            Position tete = serpent->tete->position;
            if(carte->grille[tete.x][tete.y]==FRUIT){ serpent->croissance+=3; carte->grille[tete.x][tete.y]=VIDE; placer_fruit_aleatoire(carte);}
            if(verifier_collision_murs(serpent,carte) || verifier_auto_collision(serpent)){ jeu_actif=0; printf("Game Over !\n"); }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        afficher_carte_graphique(carte,renderer);
        afficher_serpent_graphique(serpent,renderer);
        SDL_RenderPresent(renderer);
    }

    liberer_serpent(serpent);
    liberer_carte(carte);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



