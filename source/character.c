#include "character.h"
#include <SDL_image.h>
#include "common.h"


int initializeCharacter(GameState* gameState, Character* character) {
    // Initialiser les propriétés du personnage
    character->x = 70;
    character->y = 670;
    character->speed = 5.0f;
    character->width = 100;
    character->height = 120;
    
    // Variables d'animation
    character->currentFrame = 0;
    character->frameCount = 0;
    character->animationSpeed = 5;
    character->isAnimating = 0;  // Pas d'animation au départ

   



    
    // Initialiser tous les pointeurs de texture à NULL
    for (int i = 0; i < NBFRAME; i++) {
        character->textures[i] = NULL;
    }
    
    // Charger uniquement la première image au départ
    SDL_Surface* surface = IMG_Load("data/TOMATE_Profil_D_00000.png");
    if (!surface) {
        printf("Erreur de chargement de l'image: %s\n", IMG_GetError());
        return 0;
    }
    
    character->textures[0] = SDL_CreateTextureFromSurface(gameState->renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!character->textures[0]) {
        printf("Erreur de création de la texture: %s\n", SDL_GetError());
        return 0;
    }
    
    // Définir la texture courante comme la première
    character->texture = character->textures[0];
    
    return 1;
}

void updateCharacter(GameState* gameState, Character* character, PadState* pad, u64* kHeld) {
    // Cette fonction ne s'exécute que sur les pages MAP (page 2)
    if (gameState->currentPage != PAGE_PLTO1 && gameState->currentPage != PAGE_PLTO2) {
        return;
    }
    
    // Lire les valeurs du joystick
    HidAnalogStickState analog_stick_l = padGetStickPos(pad, 0);
    
    // Calculer le déplacement en fonction du joystick
    float dx = 0, dy = 0;
    
    // Valeurs seuil pour éviter les mouvements involontaires
    const int deadzone = 4000;
    *kHeld = padGetButtons(pad);
    
    if (*kHeld & HidNpadButton_Y) {
        character->speed = 10.0f;
    } else {
        character->speed = 5.0f;
    }
    
    // Appliquer les déplacements horizontaux
    if (analog_stick_l.x > deadzone) {
        dx = character->speed;
        character->isAnimating = 1;  // Activer l'animation
        
        // Gestion de l'animation
        character->frameCount++;
        if (character->frameCount >= character->animationSpeed) {
            character->frameCount = 0;
            character->currentFrame = (character->currentFrame + 1) % NBFRAME;
            
            // Charger la texture à la demande si nécessaire
            if (character->textures[character->currentFrame] == NULL) {
                char filename[100];
                if(character->currentFrame < 10){
                sprintf(filename, "data/TOMATE_Profil_D_0000%d.png", character->currentFrame);
                }else {
                    sprintf(filename, "data/TOMATE_Profil_D_000%d.png", character->currentFrame);
                }
                
                SDL_Surface* surface = IMG_Load(filename);
                if (surface) {
                    character->textures[character->currentFrame] = 
                        SDL_CreateTextureFromSurface(gameState->renderer, surface);
                    SDL_FreeSurface(surface);
                }
            }
            
            // Utiliser la texture si elle est disponible
            if (character->textures[character->currentFrame]) {
                character->texture = character->textures[character->currentFrame];
            }
        }
    } else if (analog_stick_l.x < -deadzone) {
        dx = -character->speed;
        character->isAnimating = 0;  // Désactiver l'animation pour gauche
        character->isAnimating = 1;  // Activer l'animation
        
        // Gestion de l'animation
        character->frameCount++;
        if (character->frameCount >= character->animationSpeed) {
            character->frameCount = 0;
            character->currentFrame = (character->currentFrame + 1) % NBFRAME;
            
            // Charger la texture à la demande si nécessaire
            if (character->textures[character->currentFrame] == NULL) {
                char filename[100];
                if(character->currentFrame < 10){
                sprintf(filename, "data/TOMATE_Profil_G_0000%d.png", character->currentFrame);
                }else {
                    sprintf(filename, "data/TOMATE_Profil_G_000%d.png", character->currentFrame);
                }
                
                SDL_Surface* surface = IMG_Load(filename);
                if (surface) {
                    character->textures[character->currentFrame] = 
                        SDL_CreateTextureFromSurface(gameState->renderer, surface);
                    SDL_FreeSurface(surface);
                }
            }
            
            // Utiliser la texture si elle est disponible
            if (character->textures[character->currentFrame]) {
                character->texture = character->textures[character->currentFrame];
            }
        }
    } else {
        // Si on ne bouge pas horizontalement, revenir à l'image par défaut
        character->isAnimating = 0;
        character->currentFrame = 0;
        character->frameCount = 0;
        character->texture = character->textures[0];
    }
    
    // Appliquer les déplacements verticaux
    if (analog_stick_l.y > deadzone) {
        dy = -character->speed;
    } else if (analog_stick_l.y < -deadzone) {
        dy = character->speed;
    }
    
    character->x += dx ; // Normalisation pour 60 FPS
    character->y += dy ;
    
    // Limiter le personnage à l'écran
    if (character->x < 0) character->x = 0;
    if (character->x > SCREEN_W - character->width) character->x = SCREEN_W - character->width;
    if (gameState->currentPage == PAGE_PLTO1) {
        if (character->y > SCREEN_H - character->height) {
            character->y = SCREEN_H - character->height;
        }
    }
}

void renderCharacter(GameState* gameState, Character* character) {
    // Afficher le personnage uniquement sur la page MAP
    if (gameState->currentPage != PAGE_PLTO1 && gameState->currentPage != PAGE_PLTO2) {
        return;
    }
    
    // Créer le rectangle de destination pour le personnage
    SDL_Rect dst = {
        (int)character->x,
        (int)character->y,
        character->width,
        character->height
    };
    
    // Afficher le personnage avec la texture courante
    SDL_RenderCopy(gameState->renderer, character->texture, NULL, &dst);
}
void choisirMap(GameState* gameState, Character* character) {
    if (gameState->currentPage == PAGE_PLTO1 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO2;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO2 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO1;
        character->y = 0;
    } else if (gameState->currentPage == PAGE_PLTO2 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO3;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO3 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO2;
        character->y = 0;
    } else if (gameState->currentPage == PAGE_PLTO3 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO4;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO4 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO3;
        character->y = 0;
    } else if (gameState->currentPage == PAGE_PLTO5 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO6;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO5 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO4;
        character->y = 0;
    } else if (gameState->currentPage == PAGE_PLTO6 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO7;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO6 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO5;
        character->y = 0;
    } else if (gameState->currentPage == PAGE_PLTO7 && character->y < 0) {
        gameState->currentPage = PAGE_PLTO8;
        character->y = 720;
    } else if (gameState->currentPage == PAGE_PLTO7 && character->y > 720) {
        gameState->currentPage = PAGE_PLTO6;
        character->y = 0;
    }
}
void cleanupCharacter(Character* character) {
    // Nettoyer toutes les textures
    for (int i = 0; i < NBFRAME; i++) {
        if (character->textures[i]) {
            SDL_DestroyTexture(character->textures[i]);
            character->textures[i] = NULL;
        }
    }
    character->texture = NULL;  // Ce pointeur référençait une des textures
}