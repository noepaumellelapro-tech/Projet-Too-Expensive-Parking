#include "Interface.h"
#include <stdio.h>
#include <stdbool.h>
#include "vehicule.h"

//créé une fenetre SDL
SDL_Window* SDLCreateWindow(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return  NULL;
    }

    SDL_Window* window = SDL_CreateWindow("Parking Simulation",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        printf("Erreur de fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    return window;
}

void SDLDestroyWindow(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DessinMap(SDL_Renderer* renderer, char Map[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, SDL_Rect rect) {

    //int cellW = rect.w / nb_cols;
    //int cellH = rect.h / nb_rows;

    float cellW = (float)rect.w / nb_cols;
    float cellH = (float)rect.h / nb_rows;

    for (int i = 0; i < nb_rows; i++) {
        for (int j = 0; j < nb_cols; j++) {
            char c = Map[i][j];

            SDL_FRect cell = {
            rect.x + j * cellW,
            rect.y + i * cellH,
            cellW,
            cellH
            };

            if (c == '|') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLineF(renderer,
                                   cell.x + cellW / 2, cell.y,
                                   cell.x + cellW / 2, cell.y + cellH);
            }
            else if (c == '_') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLineF(renderer,
                                   cell.x, cell.y + cellH / 2,
                                   cell.x + cellW, cell.y + cellH / 2);
            }
            else if (c == 'G') {    //green
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRectF(renderer, &cell);
            }
            else if (c == 'R') {    //red
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRectF(renderer, &cell);
            }
            else if (c == 'B') {    //blue
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRectF(renderer, &cell);
            }
            
            // sinon espace => rien
        }
    }
}

int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols, Vehicule* listeVehicules) {


    SDL_Window* window = SDLCreateWindow();

    read_map(nomFichier, Map, nb_rows, nb_cols, listeVehicules);

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Erreur création renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int screenW, screenH;
    SDL_GetWindowSize(window, &screenW, &screenH);

    int nbCols = *nb_cols;
    int nbRows = *nb_rows;

    // --- Calcul précis en flottant ---
    float cellW = (float)screenW / nbCols;
    float cellH = (float)screenH / nbRows;
    float CELL_SIZE = (cellW < cellH) ? cellW : cellH;

    // Calcul du rectangle englobant la map (en entiers pour SDL_Rect)
    SDL_Rect rect;
    rect.w = (int)(nbCols * CELL_SIZE);
    rect.h = (int)(nbRows * CELL_SIZE);
    rect.x = (screenW - rect.w) / 2;
    rect.y = (screenH - rect.h) / 2;

    // Boucle principale
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        // Fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Rectangle blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);

        DessinMap(renderer, Map, nbRows, nbCols, rect);

        SDL_RenderPresent(renderer);
    }

    SDLDestroyWindow(window, renderer);
    return 1;
}


//lecture de la map depuis un fichier et affichage
int read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols, Vehicule* listeVehicules)
{
    int i = 0; // lignes
    int j = 0; // colonnes
    int nb_col = 0;

    FILE *FichierMap = fopen(nomFichier, "r");
    if (FichierMap == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return 0; // échec
    }

    // Lecture caractère par caractère
    while (1) {
        char c = fgetc(FichierMap);

        if (feof(FichierMap))
            break;

        if (c == '\n') {

            if (i == 0){
                nb_col = j; // largeur de la première ligne
            }

            i++;
            j = 0;
            continue;
        }

        Map[i][j] = c;
        
        j++;
    }

    fclose(FichierMap);

    // Enregistrer les dimensions de la carte
    *nb_rows = i + 1;
    *nb_cols = nb_col;

    // Ajout des vehicules sur la map
    while (listeVehicules != NULL) {
        Vehicule* v = listeVehicules;

        int carUpBool = (v->direction == 'N' || v->direction == 'S') ? 1 : 0;

        //test si le vehicules peut etre placé sur la map ou il se trouve dans un mur
        for (int m = 0; m < 2 + carUpBool ; m++) {
            for (int n = 0; n < 3 - carUpBool ; n++) {
                if (Map[v->x + m][v->y + n] != ' '){
                    printf("le vehicule avec l'id %d ne peut pas etre placé sur la map\n", v->id);
                    return 0; // échec a cause d'un vehicule dans un mur
                }

                switch (v->direction) //Permet de mettre la voiture dans la bonne direction
                {
                    case 'N':
                        Map[v->x + m][v->y + n] = v->symbole[n][m];
                        break;
                    case 'S':
                        Map[v->x + m][v->y + n] = v->symbole[n][2-m];
                        break;
                    case 'E':
                        Map[v->x + m][v->y + n] = v->symbole[m][2-n];
                        break;
                    case 'O':
                        Map[v->x + m][v->y + n] = v->symbole[m][n];
                        break;
                }   
            }
        }

        listeVehicules = v->suivant;
    }

    return 1; // succès
}