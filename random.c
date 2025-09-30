#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"
#include "vehicule.h"

void random_car(){

    srand(time(NULL));

    int couleurs = rand() % 5; // 0, 1, 2
    int alignementrand = rand() % 1; // 0, 1,
    int vitesse = rand() % 5; // 0, 1, 2
    int typerand = rand() % 1;
    char type;
    char alignement;

    if(typerand == 0){
         type = 'C'; // camion
    } else if (type == 1){
         type = 'V'; // voiture
    } 

    if(alignementrand == 0){
         alignement = 'G'; // gauche
    } else if (alignementrand == 1){
         alignement = 'D'; // droite
    }



    creerVehicule(0, 0, 'N', vitesse, couleurs, alignement, type, 'M', 0, (char[2][3]){{' ', 'A', ' '}, {' ', ' ', ' '}});


    
}