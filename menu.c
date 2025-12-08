#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vehicule.h"
#include "random.h"
#include "Interface.h"

void afficherMenuPrincipal(){
    
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░\n");
    printf("\t\t\t\t\t\t░█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█░\n");
    printf("\t\t\t\t\t\t░█░▀█▀░█▀█░█▀█░░░█▀▀░█░█░█▀█░█▀▀░█▀█░█▀▀░▀█▀░█░█░█▀▀░░░█▀█░█▀█░█▀▄░█░█░▀█▀░█▀█░█▀▀░█░\n");
    printf("\t\t\t\t\t\t░█░░█░░█░█░█░█░░░█▀▀░▄▀▄░█▀▀░█▀▀░█░█░▀▀█░░█░░▀▄▀░█▀▀░░░█▀▀░█▀█░█▀▄░█▀▄░░█░░█░█░█░█░█░\n");
    printf("\t\t\t\t\t\t░█░░▀░░▀▀▀░▀▀▀░░░▀▀▀░▀░▀░▀░░░▀▀▀░▀░▀░▀▀▀░▀▀▀░░▀░░▀▀▀░░░▀░░░▀░▀░▀░▀░▀░▀░▀▀▀░▀░▀░▀▀▀░█░\n");
    printf("\t\t\t\t\t\t░█░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█░\n");
    printf("\t\t\t\t\t\t░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░▄▄▄░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░▀█░░░░░░░█▄█░█▀█░█▀▄░█▀▀░░░█▀▀░▀█▀░█▄█░█▀█░█░░░█▀▀░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░█░░░░░░░█░█░█░█░█░█░█▀▀░░░▀▀█░░█░░█░█░█▀▀░█░░░█▀▀░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░▀▀▀░▀░░░░▀░▀░▀▀▀░▀▀░░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀░░░▀▀▀░▀▀▀░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░▀▀▄░░░░░░█▄█░█▀█░█▀▄░█▀▀░░░█▀▀░█░█░▀█▀░█▀▄░█▀▀░█▄█░█▀▀░░█░█░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░▄▀░░░░░░░█░█░█░█░█░█░█▀▀░░░█▀▀░▄▀▄░░█░░█▀▄░█▀▀░█░█░█▀▀░░▀░▀░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░▀▀▀░▀░░░░▀░▀░▀▀▀░▀▀░░▀▀▀░░░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀░▀░▀▀▀░░▀░▀░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░▀▀█░░░░░░▄▀▄░█░█░▀█▀░▀█▀░▀█▀░█▀▀░█▀▄░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░▀▄░░░░░░█\\█░█░█░░█░░░█░░░█░░█▀▀░█▀▄░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░▀▀▀░▀░░░░░▀\\░▀▀▀░▀▀▀░░▀░░░▀░░▀▀▀░▀░▀░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("\t\t\t\t\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");

    char Map [MAX_ROWS][MAX_COLS];
        int rows = 0;
        int cols = 0;

    int choix;
    scanf("%d", &choix);

    if( choix == 1){
        srand((unsigned)time(NULL)); // Initialisation de la graine pour la genération aleatoire
        Vehicule *liste = NULL;   //creation de la liste de vehicule
        random_car(&liste); // Permet de générer des véhicules aleatoires et de les ajouter a la liste

        interface("Map_1.txt", Map, &rows, &cols, liste, 24, 70);
        libererliste(&liste); // Libere la memoire allouee pour la liste des vehicules

        return ;
    }else if(choix == 2){

        srand((unsigned)time(NULL)); // Initialisation de la graine pour la génération aleatoire
        Vehicule *liste = NULL;   //creation de la liste  de vehicule
        random_car(&liste); // Permet de generer des vehicules aleatoires ett de les ajouter à la liste

        interface("Map_1.txt", Map, &rows, &cols, liste, 10,100);
        libererliste(&liste); // Libere la memoire alloue pour la liste des véhicules

        return ;
    }else if(choix == 3){

        printf("Fermeture du programme...\n");
        return;
    }else{
        printf("Choix invalide. Veuillez réessayer.\n");
        return;
    }
}