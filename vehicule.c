#include <stdio.h>
#include <stdlib.h>
#include "vehicule.h"



// fonction qui permet de créer un vehicule et
Vehicule* creerVehicule(int x, int y, char direction, int vitesse, int couleur, char alignement, 
    char type, char etat, unsigned long int tps, char symbole[2][3]) {
        
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
        v->vitesse = vitesse;
        v->couleur = couleur;
        v->alignement = alignement;
        v->type = type;
        v->etat = etat;
        v->tps = tps;
        
        
        // pour copier la voiture (temporaire)
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                v->symbole[i][j] = symbole[i][j];
            }
        }
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
    int supprimervoitureliste(Vehicule **liste, unsigned int id) {
        
        Vehicule *precedent = NULL;
        Vehicule *courant = *liste;
        
        while (courant && courant->id != id) { // Parcourt la liste jusqu'à trouver la voiture avec l'ID donné
            precedent = courant;    // Sauvegarde le véhicule précédent
            courant   = courant->suivant; // Tranfere le pointeur au suivant
        }
        
        if (precedent == NULL) { // Si la voiture à supprimer est la première de la liste
            *liste = courant->suivant; // Met à jour la tête de liste
        } else {
            precedent->suivant = courant->suivant; // Saute le véhicule à supprimer
        }
        
        detruireVehicule(courant);
        return 1;
    }
    
    // Fonction qui permet d'afficher une voiture
    void afficherVehicule(Vehicule *v) {
    
        printf("ID: %u\n", v->id);
        printf("Position: (%d, %d)\n", v->x, v->y);
        printf("Direction: %c\n", v->direction);
        printf("Vitesse: %d\n", v->vitesse);
        printf("Couleur: %d\n", v->couleur);
        printf("Alignement: %c\n", v->alignement);
        printf("Type: %c\n", v->type);
        printf("État: %c\n", v->etat);
        printf("Temps sur le parking: %lu\n", v->tps);
        printf("Symbole:");
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%c ", v->symbole[i][j]);
            }
            printf("\n");
        }
    }

    // Fonction qui permet d'afficher la liste chainee des voitures
    void afficherliste(Vehicule *liste) {
        Vehicule *courant = liste;
        while (courant != NULL) {
            afficherVehicule(courant);
            courant = courant->suivant;
        }
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
        printf("liste liberée\n");
    }