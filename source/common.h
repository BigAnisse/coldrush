#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <switch.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
// Définition des constantes pour les boutons
#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define JOY_PLUS  10
#define JOY_MINUS 11
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15

// Constantes d'écran
#define SCREEN_W 1280
#define SCREEN_H 720

// Identifiants des pages
#define PAGE_ACCUEIL 0
#define PAGE_CONTENU 1
#define PAGE_MAP 2
#define MAX_IMAGES 3

// Constantes pour la vibration
#define VIBRATION_DURATION 5 // Durée de la vibration en frames (5 frames ~ 83ms à 60fps)

// Canal audio pour les effets sonores
#define SFX_CHANNEL 1

// Structure de jeu globale pour partager l'état entre les modules
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* textures[MAX_IMAGES];
    SDL_Joystick* joystick;
    int currentPage;
    int running;
} GameState;

#endif // COMMON_H