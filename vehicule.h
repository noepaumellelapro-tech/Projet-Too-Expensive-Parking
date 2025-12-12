#ifndef VEHICULE_H
#define VEHICULE_H

typedef struct vehicule{
    unsigned int id;
    int x; //position x
    int y; //position y
    char direction; //direction (N, S, E, O)
//    int vitesse;  //vitesse du véhicule
    int couleur;  //code couleur du vehicule code ansi
//    char alignement; //gauche ou droite ou haut ou bas
//    char type; //type de véhicule camoin moto ect ..
    char etat; // il bouge ou il bouge pas
    int tps; // temps passé sur le parking
    int temps_gare; // temps déjà passé garé
    int pas_parking; //pas de parking attribué
//    char symbole[2][3]; //symbole du véhicule
    int place; //place de parking attribué
    struct vehicule* suivant; //ptr vers la voiture dapres
} Vehicule;

Vehicule* creerVehicule(int x, int y, char direction, int couleur, char etat, int tps, int temps_gare, int pas_parking, int place);
void ajoutervehicule(Vehicule **liste, Vehicule *nouvellevoiture);

void detruireVehicule(Vehicule* v);

int supprimervoitureliste(Vehicule **liste);

void afficherVehicule(Vehicule *v);

void libererliste(Vehicule **liste);

#endif
