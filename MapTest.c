#include "Map.h"
#include <stdio.h>
#include <stdbool.h>

#define TILE_SIZE 16

static char Map[MAX_ROWS][MAX_COLS];
static int rows = 0, cols = 0;

// Lit la map depuis un fichier
static void read_map_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : impossible d’ouvrir %s\n", filename);
        return;
    }

    int i = 0, j = 0, maxcols = 0, c;
    while ((c = fgetc(file)) != EOF && i < MAX_ROWS) {
        if (c == '\n') { if (j > maxcols) maxcols = j; i++; j=0; }
        else Map[i][j++] = (char)c;
    }
    if (j>0) { i++; if (j>maxcols) maxcols=j; }
    rows = i; cols = maxcols;

    fclose(file);
}

// Dessine un texte avec SDL3_ttf
static void draw_text(SDL_Renderer *renderer, TTF_Font *font,
                      const char *text, int x, int y, SDL_Color color) {
    SDL_Texture *tex = TTF_RenderText(renderer, font, text, color);
    if (!tex) { SDL_Log("Erreur TTF_RenderText: %s", TTF_GetError()); return; }
    int w, h; SDL_GetTextureSize(tex, &w, &h);
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderTexture(renderer, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}

// Dessine la map
static void draw_map(SDL_Renderer *renderer, TTF_Font *font, int win_w, int win_h) {
    SDL_Color textColor = {255,255,255,255};
    SDL_Color borderColor = {255,255,0,255};
    int map_w = cols * TILE_SIZE, map_h = rows * TILE_SIZE;
    int offset_x = (win_w - map_w)/2, offset_y = (win_h - map_h)/2;

    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(Map[i][j]!=0) {
                char buf[2] = {Map[i][j], '\0'};
                draw_text(renderer, font, buf, offset_x + j*TILE_SIZE, offset_y + i*TILE_SIZE, textColor);
            }

    SDL_Rect rect = {offset_x-2, offset_y-2, map_w+4, map_h+4};
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);
}

// Fonction unique pour tout faire
void run_map(const char *filename) {
    read_map_file(filename);
    if(rows==0 || cols==0) { fprintf(stderr,"Map vide\n"); return; }

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    const int WINDOW_W=800, WINDOW_H=600;
    SDL_Window *window = SDL_CreateWindow("Map SDL3", SDL_WINDOW_SHOWN, WINDOW_W, WINDOW_H);
    SDL_Renderer *renderer = SDL_CreateRenderer(window);
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", TILE_SIZE);

    bool running = true;
    SDL_Event event;
    while(running) {
        while(SDL_PollEvent(&event))
            if(event.type==SDL_EVENT_QUIT) running=false;

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        draw_map(renderer,font,WINDOW_W,WINDOW_H);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
