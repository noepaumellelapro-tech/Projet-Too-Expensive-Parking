#include <stdio.h>
#include <stdlib.h>
#include "vehicule.h"



// fonction qui permet de créer un vehicule et
Vehicule* creerVehicule(int x, int y, char direction, int vitesse, int couleur, char alignement, 
                        char type, char etat, unsigned long int tps, char symbole[2][3]) {
                            
    Vehicule* v = (Vehicule*)malloc(sizeof(Vehicule));

    // si l'allocation échoue on alt f4

    if (v == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // les attributs du vehicule
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
void ajoutervehicule(Vehicule **debutliste, Vehicule *nouvellevoiture) {

    if (*debutliste == NULL) { // si la premiere case est vide nulll elle devient la premiere case
        *debutliste = nouvellevoiture;

    } else { // sinon on va a la derniere case et on ajouter une voiiteure
        Vehicule *parcourirliste = *debutliste;

        while (parcourirliste->suivant != NULL) { // permet de parcourir la liste jusqua que sa soit nulll
            parcourirliste = parcourirliste->suivant;
        }
        
        parcourirliste->suivant = nouvellevoiture; // une fois a la fin on ajoute une voituree
    }
}



// Fonction qui permet de supprimer une voiture de la liste
void supprimervoitureliste(Vehicule **debutliste, Vehicule *voitureasupprimer) {
    if (*debutliste == NULL || voitureasupprimer == NULL) { // dans le cas ou liste est vide ducoup ya rien a tej
        return;
    }

    // dans le cas ou c'est la premiere voiture de la liste qui doit etre supprime
    if (*debutliste == voitureasupprimer) {
        *debutliste = voitureasupprimer->suivant; // on met la deuxieme voiture en premiere
        detruireVehicule(voitureasupprimer); 
        return;
    }

    // on parcours la liste et on cherche la voiture a supprimer
    Vehicule *parcourirliste = *debutliste;
    while (parcourirliste->suivant != NULL && parcourirliste->suivant != voitureasupprimer) {
        parcourirliste = parcourirliste->suivant;
    }

    // si on trouve la voiture a supprimer
    if (parcourirliste->suivant == voitureasupprimer) {
        // la voiture à supprimer a été trouvée dans la liste
        parcourirliste->suivant = voitureasupprimer->suivant;
        detruireVehicule(voitureasupprimer);
    }
}

void afficherVehicule(Vehicule *v) {
    if (v == NULL) {
        printf("Le véhicule est NULL.\n");
        return;
    }
    printf("Position: (%d, %d)\n", v->x, v->y);
    printf("Direction: %c\n", v->direction);
    printf("Vitesse: %d\n", v->vitesse);
    printf("Couleur: %d\n", v->couleur);
    printf("Alignement: %c\n", v->alignement);
    printf("Type: %c\n", v->type);
    printf("État: %c\n", v->etat);
    printf("Temps sur le parking: %lu\n", v->tps);
    printf("Symbole:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", v->symbole[i][j]);
        }
        printf("\n");
    }
}

