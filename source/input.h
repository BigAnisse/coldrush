#ifndef INPUT_H
#define INPUT_H

#include <switch.h>
#include <SDL.h>
#include "common.h"

// Fonctions d'initialisation et de gestion des entrées
void initializeInput(PadState* pad);
void processInput(PadState* pad, GameState* gameState, u64* kDown);
void cleanupInput(SDL_Joystick* joystick);

#endif // INPUT_H