#include <stdio.h>
#include "ticketing.h"


float calculer_tarif(const Vehicule * v) {
    int duree = v->tps;
    float tarif = duree * TARIF_HORAIRE; // Conversion des minutes en heures

    printf("Le tarif pour le voiture %d est de : %.2f balles\n", v->id, tarif);
    return tarif;
 
}