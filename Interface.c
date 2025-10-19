#include "Interface.h"
#include <stdio.h>
#include <stdbool.h>

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

    int cellW = rect.w / nb_cols;
    int cellH = rect.h / nb_rows;

    for (int i = 0; i < nb_rows; i++) {
        for (int j = 0; j < nb_cols; j++) {
            char c = Map[i][j];

            SDL_Rect cell = {
                rect.x + j * cellW,
                rect.y + i * cellH,
                cellW,
                cellH
            };

            if (c == '|') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer,
                                   cell.x + cellW / 2, cell.y,
                                   cell.x + cellW / 2, cell.y + cellH);
            }
            else if (c == '_') {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer,
                                   cell.x, cell.y + cellH / 2,
                                   cell.x + cellW, cell.y + cellH / 2);
            }
            // sinon espace => rien
        }
    }
}

int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols) {


    SDL_Window* window = SDLCreateWindow();

    read_map(nomFichier, Map, nb_rows, nb_cols);

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

    //calcul de la taille idéale des cellules
    int cellW = screenW / *nb_cols;
    int cellH = screenH / *nb_rows;
    int CELL_SIZE = (cellW < cellH) ? cellW : cellH;

    // Calcul du rectangle englobant la map
    SDL_Rect rect;
    rect.w = nbCols * CELL_SIZE;
    rect.h = nbRows * CELL_SIZE;
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
int read_map(const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols)
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
            if (i == 0) nb_col = j; // largeur de la première ligne
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

    return 1; // succès
}