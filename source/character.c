#include "character.h"
#include <SDL_image.h>
#include "common.h"

int initializeCharacter(GameState* gameState, Character* character) {
    // Initialiser les propriétés du personnage
    character->x = 70;  // Positionner au centre de l'écran
    character->y =670;
    character->speed = 5.0f;      // Vitesse de déplacement
    character->width = 80;        // Taille du personnage (à ajuster)
    character->height = 90;
    
    // Charger la texture du personnage
    SDL_Surface* surface = IMG_Load("data/character.png");
    if (!surface) {
        printf("Erreur de chargement de l'image du personnage: %s\n", IMG_GetError());
        return 0;
    }
    
    character->texture = SDL_CreateTextureFromSurface(gameState->renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!character->texture) {
        printf("Erreur de création de la texture du personnage: %s\n", SDL_GetError());
        return 0;
    }
    
    return 1;
}

void updateCharacter(GameState* gameState, Character* character, PadState* pad) {
    // Cette fonction ne s'exécute que sur la page MAP (page 2)
    if (gameState->currentPage != PAGE_PLTO1 && gameState->currentPage != PAGE_PLTO2) {
        return;
    }
    
    // Lire les valeurs du joystick
    HidAnalogStickState analog_stick_l = padGetStickPos(pad, 0);
    
    // Calculer le déplacement en fonction du joystick
    float dx = 0, dy = 0;
    
    // Valeurs seuil pour éviter les mouvements involontaires
    const int deadzone = 4000;
    
    // Appliquer les déplacements horizontaux
    if (analog_stick_l.x > deadzone) {
        dx = character->speed;
    } else if (analog_stick_l.x < -deadzone) {
        dx = -character->speed;
    }
    
    // Appliquer les déplacements verticaux
    if (analog_stick_l.y > deadzone) {
        dy = -character->speed;
    } else if (analog_stick_l.y < -deadzone) {
        dy = character->speed;
    }
    
    // Mettre à jour la position du personnage
    character->x += dx;
    character->y += dy;
    
    // Limiter le personnage à l'écran
    if (character->x < 0) character->x = 0;
    if (character->x > SCREEN_W - character->width) character->x = SCREEN_W - character->width;
    if (character->y < 0) character->y = 0;
    if (character->y > SCREEN_H - character->height) character->y = SCREEN_H - character->height;
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
    
    // Afficher le personnage
    SDL_RenderCopy(gameState->renderer, character->texture, NULL, &dst);
}
void choisirMap(GameState* gameState, Character* character){
     
    if(gameState->currentPage == PAGE_PLTO1 && character->y < 10 ){
        gameState->currentPage = PAGE_PLTO2;
        character->y = 670;
        
    }

}

void cleanupCharacter(Character* character) {
    if (character->texture) {
        SDL_DestroyTexture(character->texture);
        character->texture = NULL;
    }
}