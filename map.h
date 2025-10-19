#ifndef MAP_H
#define MAP_H

#define MAX_ROWS 100
#define MAX_COLS 200

//définition des fonctions présentes dans map.c
//void print_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols);
void affichage_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols, int startx, int starty);
void affichage_interface(char Map[MAX_ROWS][MAX_COLS], int RECTANGLE_RAWS, int RECTANGLE_COLS);

void read_mapp(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS]);



#endif