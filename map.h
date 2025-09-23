#ifndef MAP_H
#define MAP_H

#define MAX_ROWS 100
#define MAX_COLS 200

//définition des fonctions présentes dans map.c
//void print_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols);
void affichage_graphique(char Map[MAX_ROWS][MAX_COLS], int rows, int cols);
void read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS]);



#endif