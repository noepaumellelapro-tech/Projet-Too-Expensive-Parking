#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "vehicule.h"

void random_car(Vehicule **liste) {

    // Générer 4 véhicules aléatoires
    for(int i =0; i<4; i++){
    int couleurs         = rand() % 5; 
    int vitesse          = rand() % 5; 
    char type            = (rand() % 2)  ? 'C' : 'V'; // C pour voiture, V pour camion
    char alignement      = (rand() % 2)  ? 'G' : 'D'; // G pour gauche, D pour droite 

     Vehicule* v = creerVehicule(0, 0, 'N', vitesse, couleurs, alignement, type, 'M', 0, (char[2][3]){{' ', 'A', ' '}, {' ', ' ', ' '}});
     ajoutervehicule(liste, v);

     return;
    }

}