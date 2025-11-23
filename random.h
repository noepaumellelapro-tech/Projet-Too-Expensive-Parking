#ifndef RANDOM_H
#define RANDOM_H
#include "vehicule.h"

void random_car(Vehicule **liste);
void liberer_place(int place);
int random_place(int places[76]) ;
void randomCarModel(char voiture[2][3]);
#endif