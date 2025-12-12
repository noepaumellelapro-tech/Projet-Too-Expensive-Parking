#include <stdio.h>
#include <stdlib.h>
#include "vehicule.h"
#include "ticketing.h"



// fonction qui permet de créer un vehicule et
Vehicule* creerVehicule(int x, int y, char direction, int couleur, char etat, int tps, int temps_gare, int pas_parking, int place) {
        
        Vehicule* v = (Vehicule*)malloc(sizeof(Vehicule));
        static unsigned int next_id = 1; // Variable statique pour générer des IDs uniques
        
        // si l'allocation échoue on alt f4
        
        if (v == NULL) {
            printf("Erreur d'allocation mémoire");
            exit(EXIT_FAILURE);
        }
        
        // les attributs du vehicule
        v->id = next_id++; // Assigner un ID unique qui va nous permettre de l'identifier
        v->x = x;
        v->y = y;
        v->direction = direction;
        v->couleur = couleur;
        v->etat = etat;
        v->tps = tps;
        v->temps_gare = temps_gare;
        v->pas_parking = pas_parking;
        v->place = place;
        
        v->suivant = NULL; // on initalise le pointeur suivant à NULL
        return v;
}
    
    
    
    
    // fonction qui permet de supprimer un vehicule de la memoire
    void detruireVehicule(Vehicule* v) {
        free(v);
    }
    
    // Permet d'ajouter une voiture a la listee de voiture
    void ajoutervehicule(Vehicule **liste, Vehicule *nouvellevoiture) {
        
        if (*liste == NULL) { // si la premiere case est vide nulll elle devient la premiere case
            *liste = nouvellevoiture;
            
        } else { // sinon on va a la derniere case et on ajouter une voiiteure
            Vehicule *parcourirliste = *liste;
            
            while (parcourirliste->suivant != NULL) { // permet de parcourir la liste jusqua que sa soit nulll
                parcourirliste = parcourirliste->suivant;
            }
            
            parcourirliste->suivant = nouvellevoiture; // une fois a la fin on ajoute une voituree
        }
    }
    
    
    
    // Fonction qui permet de supprimer une voiture de la liste
    int supprimervoitureliste(Vehicule **liste) {
        
        Vehicule *precedent = NULL;
        Vehicule *courant = *liste;
        
        while (courant != NULL) {
        if (courant->etat == 'F') {
            Vehicule *suppression = courant;

            if (precedent == NULL) {
                *liste = courant->suivant;
                courant = *liste;
            } else {
                precedent->suivant = courant->suivant;
                courant = courant->suivant;
            }
            encaisser_vehicule(suppression);
            detruireVehicule(suppression);

        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
    return 1; // succès
    }

    // qui permet de supprimer toutes les voitures de la liste
    void libererliste(Vehicule **liste) {
        Vehicule *courant = *liste;
        Vehicule *temp;
        
        while (courant != NULL) {
            temp = courant;
            courant = courant->suivant;
            detruireVehicule(temp);
        }
        
        *liste = NULL;
        //printf("liste liberée\n");
    }

