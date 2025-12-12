#include <stdio.h>
#include "ticketing.h"


float calculer_tarif(const Vehicule * v) {
    int duree = v->tps;
    float tarif = duree * TARIF_HORAIRE;
    return tarif;
 
}

static float argent_total = 0.0f;

float encaisser_vehicule(const Vehicule* v) {
    float tarif = calculer_tarif(v);
    argent_total += tarif;
    return tarif;
}

float total_argent(void) {
    return argent_total;
}