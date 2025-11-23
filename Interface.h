#ifndef INTERFACE_H
#define INTERFACE_H

#include "vehicule.h"
#include <SDL2/SDL.h>
#define MAX_ROWS 200
#define MAX_COLS 200
//#define CELL_SIZE 5  // Taille d'une cellule en pixels



SDL_Window* SDLCreateWindow();
void SDLDestroyWindow(SDL_Window* window, SDL_Renderer* renderer);
int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols, Vehicule* listeVehicules) ;
void DessinMap(SDL_Renderer* renderer, char Map[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, SDL_Rect rect) ;
int read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols);
int ajoutervehiculeMap(char Map[MAX_ROWS][MAX_COLS], Vehicule* listeVehicules);
int supprimervehiculeMap(char Map[MAX_ROWS][MAX_COLS], Vehicule* listeVehicules);
void afficherRect(SDL_Renderer* renderer, SDL_FRect* rect, int r, int g, int b);

#endif // INTERFACE_H