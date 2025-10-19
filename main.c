#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "map.h"
#include "vehicule.h"
#include "random.h"
#include "Interface.h"

int main(void)
{

    /*
    srand((unsigned)time(NULL)); // Initialisation de la graine pour la génération aléatoire
    Vehicule *liste = NULL;   //creation de la liste de vehicule
    random_car(&liste); // Permet de générer des véhicules aléatoires et de les ajouter à la liste
    afficherliste(liste);
    libererliste(&liste); // Libère la mémoire allouée pour la liste des véhicules
*/

    char Map [MAX_ROWS][MAX_COLS];
    int rows = 0;
    int cols = 0;
    //read_map("Map_2.txt", Map);


    interface ("Map_2.txt", Map, &rows, &cols);

return EXIT_SUCCESS;
}