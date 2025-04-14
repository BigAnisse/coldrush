#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include <SDL_image.h>
#include <SDL.h>

// Fonctions de gestion du personnage
int initializeCharacter(GameState* gameState, Character* character);
void updateCharacter(GameState* gameState, Character* character, PadState* pad, CollisionMap* collisionMap);
void renderCharacter(GameState* gameState, Character* character);
void cleanupCharacter(Character* character);

// Fonctions pour la carte et les collisions
int initializeCollisionMap(CollisionMap* map);
int checkCollision(Character* character, CollisionMap* map, float newX, float newY);
void cleanupCollisionMap(CollisionMap* map);
void renderCollisionMap(GameState* gameState, CollisionMap* map);

#endif // CHARACTER_H