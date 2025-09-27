#ifndef VEHICULE_H
#define VEHICULE_H

typedef struct vehicule{
    int x; //position x
    int y; //position y
    char direction; //direction (N, S, E, O)
    int vitesse;  //vitesse du véhicule
    int couleur;  //code couleur du vehicule code ansi
    char symbole[2][3]; //symbole du véhicule
    struct vehicule* suivant; //pour la voiture dapres
} Vehicule;

Vehicule* creerVehicule(int x, int y, char direction, int vitesse, int couleur, char symbole[2][3]);

void ajoutervehicule(Vehicule **debutliste, Vehicule *nouvellevoiture);

void detruireVehicule(Vehicule* v);

void supprimervoitureliste(Vehicule **debutliste, Vehicule *voitureasupprimer);

#endif