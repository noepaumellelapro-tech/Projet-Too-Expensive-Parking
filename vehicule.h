#ifndef VEHICULE_H
#define VEHICULE_H

typedef struct vehicule{
    unsigned int id;
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

void ajoutervehicule(Vehicule **liste, Vehicule *nouvellevoiture);

void detruireVehicule(Vehicule* v);

int supprimervoitureliste(Vehicule **liste, unsigned int id);

void afficherVehicule(Vehicule *v);

void afficherliste(Vehicule *liste);

void libererliste(Vehicule **liste);

#endif