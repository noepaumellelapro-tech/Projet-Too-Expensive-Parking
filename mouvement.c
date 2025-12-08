#include <stdio.h>
#include <stdlib.h>
#include "mouvement.h"
#include "random.h"
#include "ticketing.h"
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
             else if(v->place >= 56){
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
                        v->direction = 'O';
                        v->pas_parking = 18;
                        v->etat = 'G';
                    }
                    else{
                        v->direction = 'E';
                        v->pas_parking = 6;
                        v->etat = 'G';
                    }
                }
                v->x -= 1;
            }
            //derniere ligne
            else if (v->place == 10 || v->place == 75 ){
                if(v->x -1 == 57){
                    if(v->place == 10){
                        v->direction = 'O';
                        v->pas_parking = 18;
                        v->etat = 'G';
                    }
                    else{
                        v->direction = 'E';
                        v->pas_parking = 6;
                        v->etat = 'G';
                        
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
                                v->direction = 'O';
                                v->pas_parking = 18; //18 pas pour se garer
                                v->etat = 'G'; //mettre en etat garer
                            }
                            else{
                                v->direction = 'E';
                                v->pas_parking = 6; //5 pas pour se garer
                                v->etat = 'G'; //mettre en etat garer

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

// Parcours de la liste des véhicules
    while (v != NULL) {
        if (v->etat == 'M') { 

            if(v->direction == 'O' && checkCollisionVoiture(listeVehicules, v, 'O') == 0){
                alignement_colonne(v);
            }
            else if(v->direction == 'N' && checkCollisionVoiture(listeVehicules, v, 'N') == 0){
                alignement_ligne(v);
            }
        }

//Si la voiture est entrain de se garer
        if (v->etat == 'G') { 

            if (v->direction == 'O' && checkCollisionVoiture(listeVehicules, v, 'O') == 0) {
                if (v->pas_parking > 0) {
                    v->y -= 1;
                    v->pas_parking--;
                } else {
                    v->etat = 'A';     
                    v->temps_gare = 0;
                }
            }

            if (v->direction == 'E' && checkCollisionVoiture(listeVehicules, v, 'E') == 0) {
                if (v->pas_parking > 0) {
                    v->y += 1;
                    v->pas_parking--;
                } else {
                    v->etat = 'A';
                    v->temps_gare = 0;
            }
        }
    }

    // Si la voiture est entrain d'entrer dans sa place de parking
        if (v->etat == 'A') {
            v->temps_gare++;
            if (v->temps_gare >= v->tps * 10) {
                v->etat = 'R';
                if(v->direction == 'O'){
                    v->pas_parking = 7;
                }
                else if(v->direction == 'E'){
                    v->pas_parking = 6;
                }
            }
        }
        
// Si la voiture est en train de quiiter sa place de parking
        if(v->etat =='R')
         {

            if (v->direction == 'O' && checkCollisionVoiture(listeVehicules, v, 'E') == 0) {
                if (v->pas_parking > 0) {
                    v->y += 1;
                    v->pas_parking--;
                } else {
                    v->etat = 'S';     
                    liberer_place(v->place);
                    v->temps_gare = 0;
                }
            }

              if (v->direction == 'E' && checkCollisionVoiture(listeVehicules, v, 'O') == 0) {
                if (v->pas_parking > 0) {
                    v->y -= 1;
                    v->pas_parking--;
                } else {
                    v->etat = 'S';
                   liberer_place(v->place);
                    v->temps_gare = 0;
            }
        }


         }

// Si la voiture est en train de quitter le parking
         if (v->etat == 'S') {
            int EXIT_X = 1; 
            int EXIT_Y = 0;

           
                if (v->x > EXIT_X) {
                    v->direction = 'N';  
                    if (checkCollisionVoiture(listeVehicules, v, 'N') == 0)
                        v->x--;              
                }

                else if (v->y > EXIT_Y) {
                    v->direction = 'O';
                    if (checkCollisionVoiture(listeVehicules, v, 'O') == 0)  
                        v->y--;             
                }

            if (v->x == EXIT_X && v->y == EXIT_Y) {
                float tarif = calculer_tarif(v);
                v->etat = 'F';  
            }
        }


        v = v->suivant;
    }
}

int checkCollisionVoiture(Vehicule *listeVehicules, Vehicule *voitureAverif, char DirMouvement) {   //Retourne 1 si il y'a une collision potentielle au prochain mouvement, 0 sinon
    Vehicule* v = listeVehicules;

    int tmpX1 = voitureAverif->x;
    int tmpY1 = voitureAverif->y;

    switch (DirMouvement) {
        case 'N':
        tmpX1--;
        break;
        case 'S':
        tmpX1++;
        break;
        case 'E':
        tmpY1++;
        break;
        case 'O':
        tmpY1--;
        break;
    }
    
    int tmpX2 = tmpX1 + 2 + ((voitureAverif->direction == 'N' || voitureAverif->direction == 'S') ? 1 : 0);
    int tmpY2 = tmpY1 + 2 + ((voitureAverif->direction == 'N' || voitureAverif->direction == 'S') ? 0 : 1);
    
    int Bx1;
    int By1;
    int Bx2;
    int By2;

    while (v != NULL) {
        if (v->id != voitureAverif->id) {
            // Vérification qu'aucune voiture ne se trouve au moin 2 cases autour de la voitureAverifier
            
            Bx1 = v->x;
            By1 = v->y;
            Bx2 = v->x + 2 + ((v->direction == 'N' || v->direction == 'S') ? 1 : 0);
            By2 = v->y + 2 + ((v->direction == 'N' || v->direction == 'S') ? 0 : 1);
            
            if (tmpX1 <= Bx2+2 && tmpX2 >= Bx1-2 && tmpY1 <= By2+2 && tmpY2 >= By1-2) {
                return 1; // Collision détectée
            }
            /**if (tmpY <= v->y+5 && tmpY >= v->y-2 && tmpX <= v->x+5 && tmpX >= v->x-2) {
                return 1; // Collision détectée
            }*/
        }
        v = v->suivant;
    }
    return 0; // Pas de collision

}