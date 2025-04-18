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
#define PAGE_EXOLICATION 2
#define PAGE_PLTO1 3
#define MAX_IMAGES 20
#define PAGE_INTERRO 4
#define PAGE_VOLUME 5
#define PAGE_ACCEUILGROS 6
#define PAGE_CONTENUGROS 7
#define PAGE_INTERROGROS 8
#define PAGE_CROIXEXPL 9
#define PAGE_JOUEREXPL 10
#define PAGE_CROIXEXPLGROS 11
#define PAGE_JOUEREXPLGROS 12
#define PAGE_PLTO2 13
#define PAGE_PLTO3 14
#define PAGE_PLTO4 15
#define PAGE_PLTO5 16
#define PAGE_PLTO6 17
#define PAGE_PLTO7 18
#define PAGE_PLTO8 19
#define NBFRAME 25


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
// Ajouter à common.h après la déclaration de GameState



typedef struct {
    float x, y;          // Position
    float speed;         // Vitesse
    int width, height;   // Dimensions
    SDL_Texture* texture; // Texture courante
    
    // Variables pour l'animation
    SDL_Texture* textures[NBFRAME]; // Tableau de textures
    int currentFrame;    // Frame actuelle
    int frameCount;      // Compteur pour la vitesse d'animation
    int animationSpeed;  // Contrôle de la vitesse d'animation
    int isAnimating;     // Indicateur d'animation active
} Character;
#endif // COMMON_H