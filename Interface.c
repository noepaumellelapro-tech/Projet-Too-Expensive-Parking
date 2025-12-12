#include "Interface.h"
#include <stdio.h>
#include <stdbool.h>
#include "vehicule.h"
#include "mouvement.h"
#include "random.h"
#include "ticketing.h"

static SDL_Texture* createCarTexture(SDL_Renderer* renderer) {
    const char* path = "assets/car.bmp";
    SDL_Surface* surface = SDL_LoadBMP(path);
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

    float longSize =  3.0f * cellSize;       // longueur comunne
    float horizShort = 2.0f * cellSize;     // hauteur quan horizontale
    float vertNarrow = 2.2f * cellSize;     // largeur plus fine quand verticale (plus epaisse)
    float vertLong =  3.2f * cellSize;       // longueur legrement aumentée pour le vertical

    for (Vehicule* v = listeVehicules; v != NULL; v = v->suivant) {
        int vertical = (v->direction == 'N' || v->direction == 'S');

        SDL_FRect dst;
        dst.x =  mapRect.x + v->y * cellSize;
        dst.y = mapRect.y + v->x *  cellSize;
        // Pour les voitures verticales, on inverse un peu les proportios (longuer sur l'axe X, largeur sur Y apres rotation)
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

// cree une fenetre SDL (oui c'est mal ecrit exprés)
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

void afficherRect(SDL_Renderer* renderer, SDL_FRect* rect, int r, int g, int b){    // Affiche un rectange de couleur donée dans la zone definie par rect
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRectF(renderer, rect);
}

void DessinMap(SDL_Renderer* renderer, char Map[MAX_ROWS][MAX_COLS], int nb_rows, int nb_cols, SDL_Rect rect) {

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
            

            switch (c) {
                case '|':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLineF(renderer,
                                       cell.x + cellW / 2, cell.y,
                                       cell.x + cellW / 2, cell.y + cellH);
                    break;
                case '_':
                    SDL_SetRenderDrawColor(renderer,  255, 255, 255, 255);
                    SDL_RenderDrawLineF(renderer,
                                        cell.x, cell.y + cellH / 2,
                                        cell.x + cellW, cell.y + cellH / 2);
                    break;
                case 'G':   // gren
                    afficherRect(renderer, &cell, 0,  255, 0);
                    break;
                case 'R':   // rid
                    afficherRect(renderer, &cell, 255, 0, 0);
                    break;
                case 'B':   // blu
                    afficherRect(renderer, &cell, 0,  0, 255);
                    break;
                case 'Y':   // yelow
                    afficherRect(renderer, &cell, 255, 255, 0);
                    break;
                default:    // espace ou autre caractere non geré
                    break;
            }
            
        }
        
    }

    
}

int interface (const char *nomFichier, char Map[MAX_ROWS][MAX_COLS], int *nb_rows, int *nb_cols, Vehicule* listeVehicules,int delay, int chance) {


    SDL_Window* window = SDLCreateWindow();

    read_map(nomFichier, Map, nb_rows, nb_cols);

    // Creation du render (oui je sais mal orthographié)
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

    // --- Calcul presi en flottan ---
    float cellW =  (float)screenW / nbCols;
    float cellH = (float)screenH / nbRows;
    float CELL_SIZE = (cellW <  cellH) ? cellW : cellH;

    // Calcul du rectange engloban la map (en entier pour SDL_Rect)
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
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }

        // Fond noir  (basique)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Fond de la zone carte en gris beton (yes faute)
        SDL_SetRenderDrawColor(renderer, 95, 95, 95, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Rectange blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        
        //  Vehicule sur la map
        SDL_Delay(delay);

        // Permet de fair spawn des voitures toute les 5 secondes
        
        spawn_compteur++;
            if (spawn_compteur >= 20) {  // toutes les  environ toutes les 5secondess

                if (rand() % 100 < chance) { //70% de chance de spown
                    random_car(&listeVehicules);
                }

                spawn_compteur = 0;
            }


        mouvement_vehicules(listeVehicules, Map);

        supprimervoitureliste(&listeVehicules);

        DessinMap(renderer, Map, nbRows, nbCols, rect);
        drawCars(renderer, listeVehicules, rect, CELL_SIZE, carTexture);

        SDL_RenderPresent(renderer);
    }

    if (carTexture) {
        SDL_DestroyTexture(carTexture);
    }
    float total = total_argent();
    printf("Total d'argent récolté: %.2f euros\n", total);
    SDLDestroyWindow(window, renderer);
    return 0;
}

// lecture de la map depui un fichier et afichage
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
