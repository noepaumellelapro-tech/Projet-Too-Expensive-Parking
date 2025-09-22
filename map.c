#include <stdio.h>
#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 200


//affichage de la map 
void print_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols) {
    
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            //affichage du caractère
            printf("%c", Map[i][j]);

        }

        //retoiur a la ligne après chaque ligne
        
        printf("\n");
    }
    
};


//lecture de la map depuis un fichier et affichage via print_map
void read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS]) {
    
    int i = 0; //Lignes
    int j = 0; //Colonnes
    int nb_col = 0; //nombre de colonnes

    FILE *FichierMap = fopen(nomFichier, "r"); 

    //On regarde si le fichier s'est bien ouvert ou non 
    if(FichierMap == NULL){
        printf("Erreur d'ouverture du fichier");
        return ;
    }

    
    //Lecture des caractères du fichier un à un et ajout dans le tableau
     do
    {
        char c = fgetc(FichierMap);

        //check si c'est la fin du fichier
        if (feof(FichierMap)){
            break ;
        }

        //Si le caractère est un retour a la ligne on skip l'écriture dans le tableau et on passe a une autre ligne
        if(c == '\n'){
            if (i == 0) nb_col = j;
            
            i++;
            
            j = 0;
            continue ;
        }

        //ecriture du caractère dans le tableau
        Map[i][j] = c ;
        j++;

    }  while(1);


    fclose(FichierMap);
    
    print_map(Map, i + 1, nb_col); //Affichage de la map
};


