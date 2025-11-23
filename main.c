#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vehicule.h"
#include "random.h"
#include "Interface.h"

int main(void)

{   
    int places[76] = {0}; // Tableau pour gérer les places de parking (0 = libre, 1 = occupée)
    srand((unsigned)time(NULL)); // Initialisation de la graine pour la génération aléatoire
    Vehicule *liste = NULL;   //creation de la liste de vehicule
    random_car(&liste,places); // Permet de générer des véhicules aléatoires et de les ajouter à la liste

    char Map [MAX_ROWS][MAX_COLS];
    int rows = 0;
    int cols = 0;

    interface("Map_1.txt", Map, &rows, &cols, liste);
    libererliste(&liste); // Libère la mémoire allouée pour la liste des véhicules

return EXIT_SUCCESS;
}