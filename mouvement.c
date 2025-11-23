#include <stdio.h>
#include <stdlib.h>
#include "mouvement.h"

void alignement_colonne(Vehicule *v){
    //on va s'aligner a sa place (etape 1)
            //collone 1
            if (v->place < 20 ){
                if(v->y -1 == 22){
                    v->direction = 'N';
                }
                v->y -= 1;
            }//collone 2
            else if(v->place < 38 && v->place >= 20){
                if(v->y -1 == 58){
                    v->direction = 'N';
                }
                v->y -=1;
            }//colone 3
            else if(v->place < 56 && v->place >= 38){
                if(v->y -1 == 94){
                    v->direction = 'N';
                }
                v->y -=1;
            }//colone 4
            else if(v->place <= 56){
                if(v->y -1 == 130){
                    v->direction = 'N';
                }
                v->y -=1;
            }
}

void alignement_ligne(Vehicule *v){
    //on va s'aligner a la place en montant (etape 2)
            //ligne1
            if (v->place == 0 || v->place == 65 ){
                if(v->x -1 == 7){
                    if(v->place == 0){
                        v->direction = 'E';
                    }
                    else{
                        v->direction = 'O';
                    }
                }
                v->x -= 1;
            }
            //derniere ligne
            else if (v->place == 10 || v->place == 75 ){
                if(v->x -1 == 57){
                    if(v->place == 10){
                        v->direction = 'E';
                    }
                    else{
                        v->direction = 'O';
                    }
                }
                v->x -= 1;
            }
            //reste des lignes
            else{
                int z = 0;
                int i = 0;
                int j=0;
                while (z == 0)
                {
                    if(v->place == 1+i || v->place == 11+i || v->place == 20+i || v->place == 29+i || v->place == 38+i || v->place == 47+i || v->place == 56+i || v->place == 66+i){
                        if(v->x-1 == 12+j){
                            if(v->place == 1+i || v->place == 20+i || v->place == 38+i || v->place == 56+i){
                                v->direction = 'E';
                            }
                            else{
                                v->direction = 'O';
                            }
                        }
                        v->x -= 1;
                        z = 1;
                    }
                    i++;
                    j+=5;
                }
                
            }

    }
           

void mouvement_vehicules(Vehicule *listeVehicules) {
    Vehicule* v = listeVehicules;

    while (v != NULL) {
        if (v->etat == 'M') { // Si le véhicule est en mouvement

            if(v->direction == 'O'){
                alignement_colonne(v);
            }
            else if(v->direction == 'N'){
                alignement_ligne(v);
            }

            

            

        }
        v = v->suivant; // Passe au véhicule suivant
    }
}
