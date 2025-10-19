#include <stdio.h>

#include <ncurses.h>

#define MAX_ROWS 100
#define MAX_COLS 200



/*
void print_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols) {
    
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            //affichage du caractère
            printf("%c", Map[i][j]);

        }

        //retoiur a la ligne après chaque ligne
        
        printf("\n");
    }
    
};*/

void affichage_map(char Map[MAX_ROWS][MAX_COLS], int rows, int cols, int startx, int starty) {

    //initscr();              // lance curses mode
    //clear();  

    for (int i = 0; i < rows -1; i++) {

        for (int j = 0; j < cols -1 ; j++) {

            //On bouge au bon endroit
            move(startx + i ,starty + j);
            //affichage du caractère
            addch(Map[i][j]);

        }

        //retoiur a la ligne après chaque ligne
        
    }
    
    //refresh();              
    //getch();               
    //endwin();               // arret curses mode
}



void affichage_interface(char Map[MAX_ROWS][MAX_COLS], int RECTANGLE_RAWS, int RECTANGLE_COLS){

    initscr(); // prépare l'utilisation de ncurses

    start_color(); // active la gestion des couleurs

    use_default_colors(); // utilise les couleurs par défaut du terminal

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // paire de couleurs pour le texte blanc sur fond noir

    bkgd(COLOR_PAIR(1)); // définit le fond de l'écran avec la paire de couleurs
    clear();

    int terminalrows, terminalcols;

    getmaxyx(stdscr, terminalrows, terminalcols); // obtenir la taille du terminal

    //on se place au centre du terminal
    int start_y = (terminalrows - RECTANGLE_RAWS) / 2;
    int start_x = (terminalcols- RECTANGLE_COLS) / 2;

    //remplissage du rectangle le tableau MAP (efface le contenu précédent)
    affichage_map(Map, RECTANGLE_RAWS - 1, RECTANGLE_COLS - 1, start_y +1 , start_x + 1);


    //dessin des lignes du rectangle
    mvhline(start_y, start_x, ACS_HLINE, RECTANGLE_COLS); // haut
    mvhline(start_y + RECTANGLE_RAWS - 1, start_x, ACS_HLINE, RECTANGLE_COLS); // bas
    mvvline(start_y, start_x, ACS_VLINE, RECTANGLE_RAWS); // gauche
    mvvline(start_y, start_x + RECTANGLE_COLS - 1, ACS_VLINE, RECTANGLE_RAWS); // droite

    //dessin des coins du rectangle
    mvaddch(start_y, start_x, ACS_ULCORNER);
    mvaddch(start_y, start_x + RECTANGLE_COLS - 1, ACS_URCORNER);
    mvaddch(start_y + RECTANGLE_RAWS - 1, start_x, ACS_LLCORNER);
    mvaddch(start_y + RECTANGLE_RAWS - 1, start_x + RECTANGLE_COLS - 1, ACS_LRCORNER);

    refresh();   // Met à jour l’écran pour afficher le dessin
    getch();     // Attend que l’utilisateur appuie sur une touche
    endwin();    // Termine proprement la session ncurses



}





//lecture de la map depuis un fichier et affichage via print_map
void read_mapp(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS]) {
    
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
    
    //print_map(Map, i + 1, nb_col); //Affichage de la map
    affichage_interface(Map, i + 3, nb_col + 2);
};
