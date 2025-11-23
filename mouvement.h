#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include "vehicule.h"

void mouvement_vehicules(Vehicule *listeVehicules) ;

void alignement_ligne(Vehicule *v);
void alignement_colonne(Vehicule *v);
#endif