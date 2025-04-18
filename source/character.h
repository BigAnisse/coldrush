#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include "common.h"

// Fonctions de gestion du personnage
int initializeCharacter(GameState* gameState, Character* character);
void updateCharacter(GameState* gameState, Character* character, PadState* pad, u64* kHeld);
void renderCharacter(GameState* gameState, Character* character);
void choisirMap(GameState* gameState, Character* character);
void cleanupCharacter(Character* character);

#endif // CHARACTER_H