#include <stdlib.h>
#include <stdio.h>
#include "random.h"
#include "vehicule.h"

void random_car(Vehicule **liste, int places[76]) {


    int place = random_place(places); // Génère une place de parquing aléatoiremen
    printf("Place attribuée: %d\n", place);

    
    int couleurs         = rand() % 5; 
    int vitesse          = rand() % 5; 
    char type            = (rand() % 2)  ? 'C' : 'V'; // C pour voiture, V pour camion
    char alignement      = (rand() % 2)  ? 'G' : 'D'; // G pour gauche, D pour droite 
    

     Vehicule *v = creerVehicule(63, 137, 'O', vitesse, couleurs, alignement, type, 'M', 0,(char[2][3]){{'R', 'G', 'G'}, {'R', 'G', 'G'}}, place);
     ajoutervehicule(liste, v);

}
int random_place(int places[76]) {

    int place;

    do {
        place = rand() % 76; 
        
    } while (places[place] == 1); // Continue jusqu'à trouver une place libre

    places[place] = 1; // Marque la place comme occupée

    return place;
}