#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>
#define MAX_ROWS 200
#define MAX_COLS 200
//#define CELL_SIZE 5  // Taille d'une cellule en pixels



SDL_Window* SDLCreateWindow();
void SDLDestroyWindow(SDL_Window* window, SDL_Renderer* renderer);
int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols) ;
void DessinMap(SDL_Renderer* renderer, char Map[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, SDL_Rect rect) ;
int read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols);


#endif // INTERFACE_H