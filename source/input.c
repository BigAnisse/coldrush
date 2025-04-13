#include "input.h"
#include "audio.h"
#include "vibration.h"

void initializeInput(PadState* pad) {
    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    padInitializeDefault(pad);
    
    // Activation des événements de joystick SDL
    SDL_JoystickEventState(SDL_ENABLE);
}

void processInput(PadState* pad, GameState* gameState, u64* kDown) {
    // Mise à jour de l'état du pad
    padUpdate(pad);
    *kDown = padGetButtonsDown(pad);
    
    // Traitement des événements SDL
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameState->running = 0;
        }
    }
    
    if (*kDown & HidNpadButton_A) {
        activateVibration(pad);
    
        if (gameState->currentPage == PAGE_ACCUEIL) {
            playButtonSound();
            gameState->currentPage = PAGE_CONTENU;
            printf("Navigation vers la page de contenu\n");
        } else if (gameState->currentPage == PAGE_CONTENU) {
            playButtonSound();
            gameState->currentPage = PAGE_MAP;
            printf("Navigation vers la page MAP\n");
        }
    }
    
    
    // Vérifier si B a été pressé
    if (*kDown & HidNpadButton_B) {
        activateVibration(pad);
        // Si on est sur la page de contenu, revenir à la page d'accueil
        if (gameState->currentPage == PAGE_CONTENU) {
            gameState->currentPage = PAGE_ACCUEIL;
            printf("Retour à la page d'accueil\n");
        } else if(gameState->currentPage == PAGE_MAP) {
            
            gameState->currentPage = PAGE_CONTENU;
            printf("Retour à la page d'accueil\n");
        }
    }
    
    // Vérifier si + a été pressé pour quitter
    if (*kDown & HidNpadButton_Plus) {
        gameState->running = 0;
    }
}

void cleanupInput(SDL_Joystick* joystick) {
    if (joystick) 
        SDL_JoystickClose(joystick);
}