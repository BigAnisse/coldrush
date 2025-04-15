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

void processInput(PadState* pad, GameState* gameState, u64* kDown, u64* kUp) {
    // À mettre en haut de ton fichier ou dans une structure globale
static int stickWasRight = 0;
static int stickWasLeft = 0;
static int stickWasUp = 0;
static int stickWasDown = 0;

    // Mise à jour de l'état du pad
    padUpdate(pad);
    *kDown = padGetButtonsDown(pad);
    *kUp = padGetButtonsUp(pad);
    HidAnalogStickState analog_stick_2 = padGetStickPos(pad, 0);
    const int deadzone2 = 15000;
    // Traitement des événements SDL
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameState->running = 0;
        }
    }
    
    // Lire la position actuelle du stick


// FRONT VERS LA DROITE
if (!stickWasRight && (analog_stick_2.x > deadzone2 || *kDown & HidNpadButton_Right )) {
    if (gameState->currentPage == PAGE_ACCUEIL) {
        gameState->currentPage = PAGE_VOLUME;
    } else if (gameState->currentPage == PAGE_VOLUME) {
        gameState->currentPage = PAGE_CONTENU;
    }else if (gameState->currentPage == PAGE_CONTENU) {
        gameState->currentPage = PAGE_INTERRO;
    }
}

// FRONT VERS LA GAUCHE
if (!stickWasLeft && (analog_stick_2.x < -deadzone2 || *kDown & HidNpadButton_Left )) {
    if (gameState->currentPage == PAGE_INTERRO) {
        gameState->currentPage = PAGE_CONTENU;
    } else if (gameState->currentPage == PAGE_CONTENU) {
        gameState->currentPage = PAGE_VOLUME;
    }else if (gameState->currentPage == PAGE_VOLUME) {
        gameState->currentPage = PAGE_ACCUEIL;
    }
}


if (!stickWasUp && (analog_stick_2.y > deadzone2 || *kDown & HidNpadButton_Up )) {
    if (gameState->currentPage == PAGE_ACCUEIL) {
        gameState->currentPage = PAGE_VOLUME;
    } else  if (gameState->currentPage == PAGE_JOUEREXPL) {
        gameState->currentPage = PAGE_CROIXEXPL;
    }  

   


}




if(!stickWasDown && (analog_stick_2.y < -deadzone2 || *kDown & HidNpadButton_Down )) {

    if (gameState->currentPage == PAGE_VOLUME || gameState->currentPage == PAGE_CONTENU  || gameState->currentPage == PAGE_INTERRO ) {
        gameState->currentPage = PAGE_ACCUEIL;
    } else if (gameState->currentPage == PAGE_CROIXEXPL) {
        gameState->currentPage = PAGE_JOUEREXPL;
    } 






}
// Mettre à jour les états
stickWasRight = (analog_stick_2.x > deadzone2);
stickWasLeft  = (analog_stick_2.x < -deadzone2);
stickWasUp = (analog_stick_2.y > deadzone2);
stickWasDown = (analog_stick_2.y < -deadzone2);


if (*kDown & HidNpadButton_A) {
    activateVibration(pad);

    if (gameState->currentPage == PAGE_ACCUEIL) {
        playButtonSound();
        gameState->currentPage = PAGE_ACCEUILGROS;
        printf("Navigation vers la page de contenu\n");
    } else if  (gameState->currentPage == PAGE_CONTENU) {
        playButtonSound();
        gameState->currentPage = PAGE_CONTENUGROS;
        printf("Navigation vers la page de contenu\n");
    

    }
    else if  (gameState->currentPage == PAGE_INTERRO) {
        playButtonSound();
        gameState->currentPage = PAGE_INTERROGROS;
        printf("Navigation vers la page de contenu\n");
    

    }else if  (gameState->currentPage == PAGE_CROIXEXPL) {
        playButtonSound();
        gameState->currentPage = PAGE_CROIXEXPLGROS;
        printf("Navigation vers la page de contenu\n");
    

    }else if  (gameState->currentPage == PAGE_JOUEREXPL) {
        playButtonSound();
        gameState->currentPage = PAGE_JOUEREXPLGROS;
        printf("Navigation vers la page de contenu\n");
    

    }
}
    if (*kUp & HidNpadButton_A) {
        activateVibration(pad);
    
        if (gameState->currentPage == PAGE_ACCEUILGROS) {
            playButtonSound();
            gameState->currentPage = PAGE_PLTO1;
            printf("Navigation vers la page de contenu\n");
        } else if (gameState->currentPage == PAGE_CONTENUGROS) {
            playButtonSound();
            gameState->currentPage = PAGE_PLTO1;
            printf("Navigation vers la page MAP\n");
        } else if(gameState->currentPage == PAGE_INTERROGROS) {
            playButtonSound();
            gameState->currentPage = PAGE_CROIXEXPL;
            printf("Navigation vers la page MAP\n");

        }else if(gameState->currentPage == PAGE_CROIXEXPLGROS) {
            playButtonSound();
            gameState->currentPage = PAGE_INTERRO;
            printf("Navigation vers la page MAP\n");

        }else if(gameState->currentPage == PAGE_JOUEREXPLGROS) {
            playButtonSound();
            gameState->currentPage = PAGE_PLTO1;
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
        } else if(gameState->currentPage == PAGE_EXOLICATION) {
            
            gameState->currentPage = PAGE_CONTENU;
            printf("Retour à la page d'accueil\n");
        } else if(gameState->currentPage == PAGE_PLTO1) {
            gameState->currentPage = PAGE_ACCUEIL;
            printf("Retour à la page d'accueil\n");


        }else if(gameState->currentPage == PAGE_PLTO2) {
            gameState->currentPage = PAGE_ACCUEIL;
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