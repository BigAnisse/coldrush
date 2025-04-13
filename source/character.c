#include "character.h"
#include <SDL_image.h>

// Noms des fichiers d'images pour chaque direction et frame
const char* characterFiles[4][ANIMATION_FRAMES] = {
    // Direction bas (DIR_DOWN)
    {
        "data/character_down_1.png",
        "data/character_down_2.png",
        "data/character_down_3.png",
        "data/character_down_4.png"
    },
    // Direction gauche (DIR_LEFT)
    {
        "data/character_left_1.png",
        "data/character_left_2.png",
        "data/character_left_3.png",
        "data/character_left_4.png"
    },
    // Direction droite (DIR_RIGHT)
    {
        "data/character_right_1.png",
        "data/character_right_2.png",
        "data/character_right_3.png",
        "data/character_right_4.png"
    },
    // Direction haut (DIR_UP)
    {
        "data/character_up_1.png",
        "data/character_up_2.png",
        "data/character_up_3.png",
        "data/character_up_4.png"
    }
};

int initializeCharacter(GameState* gameState, Character* character) {
    // Initialiser les propriétés du personnage
    character->x = SCREEN_W / 2;  // Positionner au centre de l'écran
    character->y = SCREEN_H / 2;
    character->speed = 3.0f;      // Vitesse de déplacement
    character->width = 64;        // Taille du personnage (à ajuster)
    character->height = 64;
    character->direction = DIR_DOWN;  // Direction par défaut
    character->frame = 0;             // Frame initiale
    character->frameCounter = 0;      // Compteur d'animation
    
    // Charger toutes les textures du personnage
    for (int dir = 0; dir < 4; dir++) {
        for (int frame = 0; frame < ANIMATION_FRAMES; frame++) {
            SDL_Surface* surface = IMG_Load(characterFiles[dir][frame]);
            if (!surface) {
                printf("Erreur de chargement de l'image du personnage %s: %s\n", 
                       characterFiles[dir][frame], IMG_GetError());
                return 0;
            }
            
            character->textures[dir][frame] = SDL_CreateTextureFromSurface(gameState->renderer, surface);
            SDL_FreeSurface(surface);
            
            if (!character->textures[dir][frame]) {
                printf("Erreur de création de la texture: %s\n", SDL_GetError());
                return 0;
            }
        }
    }
    
    return 1;
}

void updateCharacter(GameState* gameState, Character* character, PadState* pad, CollisionMap* collisionMap) {
    // Cette fonction ne s'exécute que sur la page MAP (page 2)
    if (gameState->currentPage != PAGE_MAP) {
        return;
    }
    
    // Lire les valeurs du joystick
    HidAnalogStickState analog_stick_l = padGetStickPos(pad, 0);
    
    // Valeurs seuil pour éviter les mouvements involontaires
    const int deadzone = 4000;
    
    // Variables pour la nouvelle position potentielle
    float newX = character->x;
    float newY = character->y;
    
    // Déterminer le mouvement et la direction
    int isMoving = 0;
    
    // Appliquer les déplacements horizontaux
    if (analog_stick_l.x > deadzone) {
        newX += character->speed;
        character->direction = DIR_RIGHT;
        isMoving = 1;
    } else if (analog_stick_l.x < -deadzone) {
        newX -= character->speed;
        character->direction = DIR_LEFT;
        isMoving = 1;
    }
    
    // Appliquer les déplacements verticaux
    if (analog_stick_l.y > deadzone) {
        newY += character->speed;
        character->direction = DIR_DOWN;
        isMoving = 1;
    } else if (analog_stick_l.y < -deadzone) {
        newY -= character->speed;
        character->direction = DIR_UP;
        isMoving = 1;
    }
    
    // Vérifier les collisions avant de mettre à jour la position
    // Tester d'abord le mouvement horizontal
    if (!checkCollision(character, collisionMap, newX, character->y)) {
        character->x = newX;
    }
    
    // Tester ensuite le mouvement vertical
    if (!checkCollision(character, collisionMap, character->x, newY)) {
        character->y = newY;
    }
    
    // Limiter le personnage à l'écran
    if (character->x < 0) character->x = 0;
    if (character->x > SCREEN_W - character->width) character->x = SCREEN_W - character->width;
    if (character->y < 0) character->y = 0;
    if (character->y > SCREEN_H - character->height) character->y = SCREEN_H - character->height;
    
    // Gérer l'animation seulement si le personnage bouge
    if (isMoving) {
        character->frameCounter++;
        if (character->frameCounter >= ANIMATION_SPEED) {
            character->frameCounter = 0;
            character->frame = (character->frame + 1) % ANIMATION_FRAMES;
        }
    } else {
        // Si le personnage ne bouge pas, remettre à la frame de base
        character->frame = 0;
    }
}

void renderCharacter(GameState* gameState, Character* character) {
    // Afficher le personnage uniquement sur la page MAP
    if (gameState->currentPage != PAGE_MAP) {
        return;
    }
    
    // Créer le rectangle de destination pour le personnage
    SDL_Rect dst = {
        (int)character->x,
        (int)character->y,
        character->width,
        character->height
    };
    
    // Afficher la texture correspondant à la direction et à la frame
    SDL_RenderCopy(gameState->renderer, 
                   character->textures[character->direction][character->frame], 
                   NULL, &dst);
}

void cleanupCharacter(Character* character) {
    // Libérer toutes les textures
    for (int dir = 0; dir < 4; dir++) {
        for (int frame = 0; frame < ANIMATION_FRAMES; frame++) {
            if (character->textures[dir][frame]) {
                SDL_DestroyTexture(character->textures[dir][frame]);
                character->textures[dir][frame] = NULL;
            }
        }
    }
}

// Exemple de carte de collision simple
int initializeCollisionMap(CollisionMap* map) {
    map->width = 20;        // Largeur de la carte en tuiles
    map->height = 11;       // Hauteur de la carte en tuiles
    map->tileSize = 64;     // Taille d'une tuile en pixels
    
    // Allouer de la mémoire pour 10 obstacles
    map->obstacleCount = 10;
    map->obstacles = (Obstacle*)malloc(map->obstacleCount * sizeof(Obstacle));
    
    if (!map->obstacles) {
        printf("Erreur d'allocation mémoire pour les obstacles\n");
        return 0;
    }
    
    // Définir quelques obstacles exemple
    // Obstacle en haut à gauche
    map->obstacles[0].x = 100;
    map->obstacles[0].y = 100;
    map->obstacles[0].width = 100;
    map->obstacles[0].height = 100;
    
    // Obstacle en bas à droite
    map->obstacles[1].x = 800;
    map->obstacles[1].y = 500;
    map->obstacles[1].width = 150;
    map->obstacles[1].height = 80;
    
    // Obstacle au milieu
    map->obstacles[2].x = 400;
    map->obstacles[2].y = 300;
    map->obstacles[2].width = 200;
    map->obstacles[2].height = 50;
    
    // Mur horizontal en haut
    map->obstacles[3].x = 300;
    map->obstacles[3].y = 50;
    map->obstacles[3].width = 500;
    map->obstacles[3].height = 30;
    
    // Mur vertical à gauche
    map->obstacles[4].x = 50;
    map->obstacles[4].y = 200;
    map->obstacles[4].width = 30;
    map->obstacles[4].height = 400;
    
    // Obstacle en haut à droite
    map->obstacles[5].x = 1000;
    map->obstacles[5].y = 100;
    map->obstacles[5].width = 120;
    map->obstacles[5].height = 120;
    
    // Obstacle en bas à gauche
    map->obstacles[6].x = 150;
    map->obstacles[6].y = 550;
    map->obstacles[6].width = 100;
    map->obstacles[6].height = 100;
    
    // Obstacle petit au centre
    map->obstacles[7].x = 600;
    map->obstacles[7].y = 400;
    map->obstacles[7].width = 50;
    map->obstacles[7].height = 50;
    
    // Obstacle en forme de L
    map->obstacles[8].x = 900;
    map->obstacles[8].y = 300;
    map->obstacles[8].width = 100;
    map->obstacles[8].height = 200;
    
    // Dernier obstacle
    map->obstacles[9].x = 700;
    map->obstacles[9].y = 150;
    map->obstacles[9].width = 80;
    map->obstacles[9].height = 80;
    
    return 1;
}

// Fonction pour vérifier les collisions
int checkCollision(Character* character, CollisionMap* map, float newX, float newY) {
    // Créer un rectangle pour la nouvelle position du personnage
    SDL_Rect charRect = {
        (int)newX,
        (int)newY,
        character->width,
        character->height
    };
    
    // Vérifier la collision avec chaque obstacle
    for (int i = 0; i < map->obstacleCount; i++) {
        SDL_Rect obstRect = {
            map->obstacles[i].x,
            map->obstacles[i].y,
            map->obstacles[i].width,
            map->obstacles[i].height
        };
        
        // Tester si les rectangles se chevauchent
        if (SDL_HasIntersection(&charRect, &obstRect)) {
            return 1; // Collision détectée
        }
    }
    
    return 0; // Pas de collision
}

void cleanupCollisionMap(CollisionMap* map) {
    if (map->obstacles) {
        free(map->obstacles);
        map->obstacles = NULL;
    }
}

// Fonction pour dessiner les obstacles (utile pour le débogage)
void renderCollisionMap(GameState* gameState, CollisionMap* map) {
    // N'afficher que sur la page MAP
    if (gameState->currentPage != PAGE_MAP) {
        return;
    }
    
    // Définir la couleur pour les obstacles (semi-transparente)
    SDL_SetRenderDrawColor(gameState->renderer, 255, 0, 0, 128);
    
    // Dessiner chaque obstacle
    for (int i = 0; i < map->obstacleCount; i++) {
        SDL_Rect obstRect = {
            map->obstacles[i].x,
            map->obstacles[i].y,
            map->obstacles[i].width,
            map->obstacles[i].height
        };
        
        SDL_RenderFillRect(gameState->renderer, &obstRect);
    }
}