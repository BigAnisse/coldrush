// Ajouter après les définitions existantes

// Constantes pour l'animation
#define ANIMATION_FRAMES 4       // Nombre d'images par animation
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

// Structure pour représenter le personnage
typedef struct {
    float x;                         // Position X
    float y;                         // Position Y
    float speed;                     // Vitesse de déplacement
    int width;                       // Largeur
    int height;                      // Hauteur
    int direction;                   // Direction actuelle
    int frame;                       // Frame d'animation actuelle
    int frameCounter;                // Compteur pour gérer la vitesse d'animation
    SDL_Texture* textures[4][ANIMATION_FRAMES]; // Textures pour chaque direction et frame
} Character;

// Structure pour une carte avec collisions
typedef struct {
    int width;                       // Largeur de la carte en tuiles
    int height;                      // Hauteur de la carte en tuiles
    int tileSize;                    // Taille d'une tuile en pixels
    Obstacle* obstacles;             // Tableau des obstacles
    int obstacleCount;               // Nombre d'obstacles
} CollisionMap;