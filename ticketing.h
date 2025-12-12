#ifndef TICKETING_H
#define TICKETING_H
#include "vehicule.h"

#define TARIF_HORAIRE 0.2

float calculer_tarif(const Vehicule* v);
float encaisser_vehicule(const Vehicule* v);
float total_argent(void);

#endif