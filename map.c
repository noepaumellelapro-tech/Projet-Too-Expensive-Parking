#include <stdio.h>

void read_map(const char *nomFichier){

    FILE *map = fopen(nomFichier, "r"); 

    //On regarde si le fichier s'est bien ouvert ou non 
    if(map == NULL){
        printf("Erreur d'ouverture du fichier");
    }
    
    //Lecture des caractères du fichier un à un 
     do
    {
        char c = fgetc(map);

        //check si c'est la fin du fichier
        if (feof(map)){
            break ;
        }

        printf("%c", c);

    }  while(1);


    fclose(map);
}

