#include <stdlib.h>
#include "random.h"
#include "vehicule.h"
#include <stdio.h>

void random_car(Vehicule **liste, int places[76]) {


    int place = random_place(places); // Génère une place de parquing aléatoiremen

    int couleurs         = rand() % 5; 
    int vitesse          = rand() % 5; 
    char type            = (rand() % 2)  ? 'C' : 'V'; // C pour voiture, V pour camion
    char alignement      = (rand() % 2)  ? 'G' : 'D'; // G pour gauche, D pour droite 
    
    char t[2][3];
    randomCarModel(t);

    Vehicule *v = creerVehicule(63, 137, 'O', vitesse, couleurs, alignement, type, 'M', 0, t, place);
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
void randomCarModel(char voiture[2][3]) {
    int NbLignes = 0;
    
    FILE *FichierVoitures = fopen("ModelesVoitures", "r");
    if (FichierVoitures == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return; // échec
    }

    while (1) { // Compte le nombre de voitures dans le fichier (1 ligne = 1 voiture)
        char c = fgetc(FichierVoitures);

        if (feof(FichierVoitures))
            break;
        if (c == '\n') {
            NbLignes++;
        }
    }

    rewind(FichierVoitures); // Revenir au début du fichier

    for (int i = rand() % NbLignes; i!=0; i--) {    //Place le curseur sur une voiture selectionné aléatoirement
        while (1){
            char c = fgetc(FichierVoitures);
            if (c == '\n')
                break;
            if (feof(FichierVoitures))
                break;
        }
    }

    // Mise de la voiture sélectionnée dans le tableau donné en argument
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            char c = fgetc(FichierVoitures);
            voiture[i][j] = c;
        }
    }

    fclose(FichierVoitures);

    return;
}