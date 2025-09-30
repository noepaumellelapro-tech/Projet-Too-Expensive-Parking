#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"
#include "vehicule.h"

void random_car(){

    srand(time(NULL));

    int couleurs = rand() % 5; // 0, 1, 2
    int alignement = rand() % 1; // 0, 1,
    int vitesse = rand() % 5; // 0, 1, 2

    creerVehicule(0, 0, 'N', vitesse, couleurs, alignement, 'C', 'M', 0, (char[2][3]){{' ', 'A', ' '}, {' ', ' ', ' '}});


    
}