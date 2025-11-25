#include "Interface.h"
#include <stdio.h>
#include <stdbool.h>
#include "vehicule.h"
#include "mouvement.h"
#include "random.h"

static SDL_Surface* createFallbackCarSurface(void) {
    const int texW = 120;
    const int texH = 80;
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, texW, texH, 32, SDL_PIXELFORMAT_RGBA32);
    if (!surface) return NULL;

    // Couleur de base (gris clair) et détails simples
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 200, 200, 200, 255));
    SDL_Rect cabine = { texW / 4, texH / 5, texW / 2, (texH * 3) / 5 };
    SDL_FillRect(surface, &cabine, SDL_MapRGBA(surface->format, 240, 240, 240, 255));

    SDL_Rect vitre = { texW / 3, texH / 4, texW / 3, texH / 2 };
    SDL_FillRect(surface, &vitre, SDL_MapRGBA(surface->format, 30, 30, 40, 220));

    SDL_Rect phareAvant = { texW - 12, texH / 3, 10, texH / 6 };
    SDL_Rect phareArriere = { 2, texH / 3, 10, texH / 6 };
    SDL_FillRect(surface, &phareAvant, SDL_MapRGBA(surface->format, 255, 230, 120, 255));
    SDL_FillRect(surface, &phareArriere, SDL_MapRGBA(surface->format, 200, 40, 40, 255));

    SDL_Rect roue1 = { texW / 6, texH / 12, texW / 5, texH / 6 };
    SDL_Rect roue2 = { texW / 6, texH - texH / 4, texW / 5, texH / 6 };
    SDL_Rect roue3 = { texW - texW / 3, texH / 12, texW / 5, texH / 6 };
    SDL_Rect roue4 = { texW - texW / 3, texH - texH / 4, texW / 5, texH / 6 };
    Uint32 pneu = SDL_MapRGBA(surface->format, 25, 25, 25, 255);
    SDL_FillRect(surface, &roue1, pneu);
    SDL_FillRect(surface, &roue2, pneu);
    SDL_FillRect(surface, &roue3, pneu);
    SDL_FillRect(surface, &roue4, pneu);

    return surface;
}

static SDL_Texture* createCarTexture(SDL_Renderer* renderer) {
    const char* path = "assets/car.bmp";
    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface) {
        SDL_Log("Impossible de charger %s (%s), utilisation d'une texture fallback.", path, SDL_GetError());
        surface = createFallbackCarSurface();
    }
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) return NULL;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return texture;
}

static void colorForVehicle(int code, Uint8* r, Uint8* g, Uint8* b) {
    switch (code % 5) {
        case 0: *r = 200; *g = 40;  *b = 40;  break; // rouge
        case 1: *r = 40;  *g = 180; *b = 60;  break; // vert
        case 2: *r = 40;  *g = 90;  *b = 200; break; // bleu
        case 3: *r = 230; *g = 200; *b = 30;  break; // jaune
        default:*r = 190; *g = 190; *b = 190; break; // gris
    }
}

static void drawCars(SDL_Renderer* renderer, Vehicule* listeVehicules, SDL_Rect mapRect, float cellSize, SDL_Texture* carTexture) {
    if (!carTexture) return;

    static int texW = 0;
    static int texH = 0;
    if (texW == 0 || texH == 0) {
        SDL_QueryTexture(carTexture, NULL, NULL, &texW, &texH);
        if (texW == 0 || texH == 0) return;
    }

    float longSize = 3.0f * cellSize;       // longueur commune
    float horizShort = 2.0f * cellSize;     // hauteur quand horizontale
    float vertNarrow = 2.2f * cellSize;     // largeur plus fine quand verticale (plus épaisse)
    float vertLong = 3.2f * cellSize;       // longueur légèrement augmentée pour le vertical

    for (Vehicule* v = listeVehicules; v != NULL; v = v->suivant) {
        int vertical = (v->direction == 'N' || v->direction == 'S');

        SDL_FRect dst;
        dst.x = mapRect.x + v->y * cellSize;
        dst.y = mapRect.y + v->x * cellSize;
        // Pour les voitures verticales, on inverse les proportions (longueur sur l'axe X, largeur sur Y après rotation)
        dst.w = vertical ? vertLong : longSize;
        dst.h = vertical ? vertNarrow : horizShort;

        double angle = 0.0;
        switch (v->direction) {
            case 'N': angle = -90.0; break;
            case 'E': angle = 0.0;   break;
            case 'S': angle = 90.0;  break;
            case 'O': angle = 180.0; break;
            default: break;
        }

        Uint8 r, g, b;
        colorForVehicle(v->couleur, &r, &g, &b);
        SDL_SetTextureColorMod(carTexture, r, g, b);
        SDL_RenderCopyExF(renderer, carTexture, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
    }
}

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

void afficherRect(SDL_Renderer* renderer, SDL_FRect* rect, int r, int g, int b){    //Affiche un rectangle de couleur donnée dans la zone définie par rect
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRectF(renderer, rect);
}

void setInnerRect(SDL_FRect* innerRect, char c, char Map[MAX_ROWS][MAX_COLS], int i, int j, int x, int y, int w, int h){  //definit la taille du rectangle interne (pour les vitres)
    
    //Position et taille par défaut du rectangle interne
    innerRect->x = x + w * 0.25f;
    innerRect->y = y + h * 0.25f;
    innerRect->w = w * 0.5f;
    innerRect->h = h * 0.5f;

    //On trouve la direction dans laquelle on oriente le carré blanc (vitre de la voiture)
    if (Map[i][j+1] == c){   //droite
        innerRect->w = w * 0.8f;
    } else if (Map[i][j-1] == c){ //gauche
        innerRect->x = x;
        innerRect->w = w * 0.75f;
    } else if (Map[i-1][j] == c){ //haut
        innerRect->y = y;
        innerRect->h = h * 0.75f;
    } else if (Map[i+1][j] == c){ //bas
        innerRect->h = h * 0.8f;
    }
}

void DessinMap(SDL_Renderer* renderer, char Map[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, SDL_Rect rect) {

    float cellW = (float)rect.w / nb_cols;
    float cellH = (float)rect.h / nb_rows;
    
    SDL_FRect innerRect;   //variable pour definir la taille et la position des rectangles internes

        for (int i = 0; i < nb_rows; i++) {
            for (int j = 0; j < nb_cols; j++) {
                char c = Map[i][j];

            SDL_FRect cell = {
            rect.x + j * cellW,
            rect.y + i * cellH,
            cellW,
            cellH
            };
            

            switch (c) {
                case '|':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLineF(renderer,
                                       cell.x + cellW / 2, cell.y,
                                       cell.x + cellW / 2, cell.y + cellH);
                    break;
                case '_':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLineF(renderer,
                                        cell.x, cell.y + cellH / 2,
                                        cell.x + cellW, cell.y + cellH / 2);
                    break;
                case 'G':   //green
                    afficherRect(renderer, &cell, 0, 255, 0);
                    break;
                case 'g': //green with middle white rectangle
                    afficherRect(renderer, &cell, 0, 255, 0);
                    setInnerRect(&innerRect, 'g', Map, i, j, cell.x, cell.y, cellW, cellH);
                    afficherRect(renderer, &innerRect, 255, 255, 255);
                    break;
                case 'R':   //red
                    afficherRect(renderer, &cell, 255, 0, 0);
                    break;
                case 'r': //red with middle white rectangle
                    afficherRect(renderer, &cell, 255, 0, 0);
                    setInnerRect(&innerRect, 'r', Map, i, j, cell.x, cell.y, cellW, cellH);
                    afficherRect(renderer, &innerRect, 255, 255, 255);
                    break;
                case 'B':   //blue
                    afficherRect(renderer, &cell, 0, 0, 255);
                    break;
                case 'b': //blue with middle white rectangle
                    afficherRect(renderer, &cell, 0, 0, 255);
                    setInnerRect(&innerRect, 'b', Map, i, j, cell.x, cell.y, cellW, cellH);
                    afficherRect(renderer, &innerRect, 255, 255, 255);
                    break;
                case 'Y':   //Yellow
                    afficherRect(renderer, &cell, 255, 255, 0);
                    break;
                case 'y': //yellow with middle white rectangle
                    afficherRect(renderer, &cell, 255, 255, 0);
                    setInnerRect(&innerRect, 'y', Map, i, j, cell.x, cell.y, cellW, cellH);
                    afficherRect(renderer, &innerRect, 255, 255, 255);
                default:    // espace ou autre caractère non géré
                    break;
            }
            
        }
        
    }

    
}

int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols, Vehicule* listeVehicules) {


    SDL_Window* window = SDLCreateWindow();

    read_map(nomFichier, Map, nb_rows, nb_cols);
    char baseMap[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < *nb_rows; i++) {
        for (int j = 0; j < *nb_cols; j++) {
            baseMap[i][j] = Map[i][j];
        }
    }

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
    rect.x = (screenW - rect.w) / 2 ;
    rect.y = (screenH - rect.h) / 2;

    SDL_Texture* carTexture = createCarTexture(renderer);

    // Boucle principale
    SDL_Event event;
    bool quit = false;
    int spawn_compteur = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        // Fond noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Fond de la zone carte en gris béton
        SDL_SetRenderDrawColor(renderer, 95, 95, 95, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Rectangle blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        
        //Vehicule sur la map
        SDL_Delay(100);

        //Permet de faire spawn des voitures toutes les 5 secondes
        
        spawn_compteur++;
            if (spawn_compteur >= 20) {  // toutes les  environ toutes les 5secondess

                if (rand() % 100 < 70) { //70% de chance de spown
                    random_car(&listeVehicules);
                }

                spawn_compteur = 0;
            }


        supprimervehiculeMap(Map,listeVehicules);
        //A changer par une fonction de deplacement des vehicules
        mouvement_vehicules(listeVehicules);

        supprimervoitureliste(&listeVehicules);

        ajoutervehiculeMap(Map, listeVehicules);

        DessinMap(renderer, baseMap, nbRows, nbCols, rect);
        drawCars(renderer, listeVehicules, rect, CELL_SIZE, carTexture);

        SDL_RenderPresent(renderer);
    }

    if (carTexture) {
        SDL_DestroyTexture(carTexture);
    }
    SDLDestroyWindow(window, renderer);
    return 0;
}


int ajoutervehiculeMap(char Map[MAX_ROWS][MAX_COLS], Vehicule* listeVehicules){
    // Ajout des vehicules sur la map
    while (listeVehicules != NULL) {
        Vehicule* v = listeVehicules;

        int carUpBool = (v->direction == 'N' || v->direction == 'S') ? 1 : 0;

        //test si le vehicules peut etre placé sur la map ou il se trouve dans un mur
        for (int m = 0; m < 2 + carUpBool ; m++) {
            for (int n = 0; n < 3 - carUpBool ; n++) {
                if (Map[v->x + m][v->y + n] != ' '){
                    printf("le vehicule avec l'id %d ne peut pas etre placé sur la map\n", v->id);
                    continue; // échec a cause d'un vehicule dans un mur / autre vehicule
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

int supprimervehiculeMap(char Map[MAX_ROWS][MAX_COLS], Vehicule* listeVehicules) {

    while (listeVehicules != NULL) {
        Vehicule* v = listeVehicules;

        int carUpBool = (v->direction == 'N' || v->direction == 'S') ? 1 : 0;

        // On enlève simplement toutes les cases occupées par le véhicule
        for (int m = 0; m < 2 + carUpBool ; m++) {
            for (int n = 0; n < 3 - carUpBool ; n++) {
                Map[v->x + m][v->y + n] = ' ';
            }
        }

        listeVehicules = v->suivant;
    }

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

    return 1;

    
}
