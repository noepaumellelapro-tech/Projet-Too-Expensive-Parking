#ifndef MAP_H
#define MAP_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Taille maximale de la map
#define MAX_ROWS 100
#define MAX_COLS 200

// Fonction unique qui lance tout : lecture de map, création fenêtre SDL3, rendu et boucle principale
void run_map(const char *filename);

#endif // MAP_H