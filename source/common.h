#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <switch.h>

// Constantes pour l'écran
#define SCREEN_W 1280
#define SCREEN_H 720

// Pages
#define PAGE_ACCUEIL 1
#define PAGE_CONTENU 0
#define PAGE_MAP 3

// Constantes pour la vibration
#define VIBRATION_DURATION 12  // ~200ms à 60 FPS

// Constantes pour l'audio
#define SFX_CHANNEL 1  // Canal dédié pour les effets sonores

// Maximum d'images à charger
#define MAX_IMAGES 4

// Constantes pour l'animation
#define ANIMATION_FRAMES 25       // Nombre d'images par animation
#define ANIMATION_FRAMESGLA 50
#define ANIMATION_SPEED 8        // Vitesse de l'animation (plus petit = plus rapide)

// Constantes pour les directions
#define DIR_DOWN  0
#define DIR_LEFT  1
#define DIR_RIGHT 2
#define DIR_UP    3

// Structure pour un obstacle
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Obstacle;

// Prédéfinition des structures pour éviter les dépendances circulaires
typedef struct Character Character;
typedef struct CollisionMap CollisionMap;
typedef struct GameState GameState;

// Structure pour représenter le personnage
struct Character {
    float x;                         // Position X
    float y;                         // Position Y
    float speed;                     // Vitesse de déplacement
    int width;                       // Largeur
    int height;                      // Hauteur
    int direction;                   // Direction actuelle
    int frame;                       // Frame d'animation actuelle
    int frameCounter;                // Compteur pour gérer la vitesse d'animation
    SDL_Texture* textures[4][ANIMATION_FRAMES]; // Textures pour chaque direction et frame
    SDL_Texture* texturesGlac[2][ANIMATION_FRAMESGLA];
};

// Structure pour une carte avec collisions
struct CollisionMap {
    int width;                       // Largeur de la carte en tuiles
    int height;                      // Hauteur de la carte en tuiles
    int tileSize;                    // Taille d'une tuile en pixels
    Obstacle* obstacles;             // Tableau des obstacles
    int obstacleCount;               // Nombre d'obstacles
};

// Structure principale pour l'état du jeu
struct GameState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Joystick* joystick;
    SDL_Texture* textures[MAX_IMAGES];
    int currentPage;
    int running;
};

#endif // COMMON_H