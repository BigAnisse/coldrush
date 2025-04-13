#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include "common.h"

// Fonctions de gestion graphique
int initializeGraphics(GameState* gameState);
void renderFrame(GameState* gameState);
void cleanupGraphics(GameState* gameState);

#endif // GRAPHICS_H