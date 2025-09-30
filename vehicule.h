#ifndef VEHICULE_H
#define VEHICULE_H

typedef struct vehicule{
    int x; //position x
    int y; //position y
    char direction; //direction (N, S, E, O)
    int vitesse;  //vitesse du véhicule
    int couleur;  //code couleur du vehicule code ansi
    char alignement; //gauche ou droite ou haut ou bas
    char type; //type de véhicule camoin moto ect ..
    char etat; // il bouge ou il bouge pas
    unsigned long int tps; // temps passé sur le parking
    char symbole[2][3]; //symbole du véhicule
    struct vehicule* suivant; //ptr vers la voiture dapres
} Vehicule;

Vehicule* creerVehicule(int x, int y, char direction, int vitesse, int couleur, char alignement, char type, char etat, unsigned long int tps, char symbole[2][3]);

void ajoutervehicule(Vehicule **debutliste, Vehicule *nouvellevoiture);

void detruireVehicule(Vehicule* v);

void supprimervoitureliste(Vehicule **debutliste, Vehicule *voitureasupprimer);

void afficherVehicule(Vehicule *v);

#endif