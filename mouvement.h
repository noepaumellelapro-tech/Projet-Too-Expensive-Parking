#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include "vehicule.h"
#define MAX_ROWS 200
#define MAX_COLS 200

void mouvement_vehicules(Vehicule *listeVehicules, char Map[MAX_ROWS][MAX_COLS]) ;
void alignement_ligne(Vehicule *v);
void alignement_colonne(Vehicule *v);
int checkCollisionVoiture(Vehicule *listeVehicules, Vehicule *voitureAverifier, char DirMouvement);
void changer_etat_place(Vehicule *v, char Etat, char Map[MAX_ROWS][MAX_COLS]);
#endif