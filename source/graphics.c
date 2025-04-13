#include "graphics.h"

int initializeGraphics(GameState* gameState) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
        printf("Erreur d'initialisation SDL: %s\n", SDL_GetError());
        return 0;
    }
    
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("Erreur d'initialisation SDL_image: %s\n", IMG_GetError());
        return 0;
    }
    
    // Création de la fenêtre et du renderer
    gameState->window = SDL_CreateWindow("Menu Switch", 
                                      SDL_WINDOWPOS_CENTERED, 
                                      SDL_WINDOWPOS_CENTERED, 
                                      SCREEN_W, SCREEN_H, 
                                      SDL_WINDOW_SHOWN);
    if (!gameState->window) {
        printf("Erreur de création de fenêtre: %s\n", SDL_GetError());
        return 0;
    }
    
    gameState->renderer = SDL_CreateRenderer(gameState->window, -1, SDL_RENDERER_SOFTWARE);
    if (!gameState->renderer) {
        printf("Erreur de création du renderer: %s\n", SDL_GetError());
        return 0;
    }
    
    // Tableau des chemins d'images
    const char* imagePaths[MAX_IMAGES] = {
        "data/acceuil.png",  // Image d'accueil (page 0)
        "data/menu.png",      // Image de contenu (page 1)
        "data/map.png"
    };
    
    // Charger les textures
    for (int i = 0; i < MAX_IMAGES; i++) {
        SDL_Surface* image = IMG_Load(imagePaths[i]);
        if (image) {
            gameState->textures[i] = SDL_CreateTextureFromSurface(gameState->renderer, image);
            SDL_FreeSurface(image);
            printf("Image %d chargée: %s\n", i, imagePaths[i]);
        } else {
            printf("Erreur de chargement de l'image %s: %s\n", imagePaths[i], IMG_GetError());
        }
    }
    
    return 1;
}

void renderFrame(GameState* gameState) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gameState->renderer);
    
    // Dessiner la page courante
    SDL_Rect dst = { 0, 0, SCREEN_W, SCREEN_H };
    if (gameState->textures[gameState->currentPage]) {
        SDL_RenderCopy(gameState->renderer, gameState->textures[gameState->currentPage], NULL, &dst);
    }
    
    // Présenter le rendu
    SDL_RenderPresent(gameState->renderer);
}

void cleanupGraphics(GameState* gameState) {
    for (int i = 0; i < MAX_IMAGES; i++) {
        if (gameState->textures[i]) 
            SDL_DestroyTexture(gameState->textures[i]);
    }
    
    SDL_DestroyRenderer(gameState->renderer);
    SDL_DestroyWindow(gameState->window);
    IMG_Quit();
    SDL_Quit();
}