#include "main.h"

int main(int argc, char** argv) {
    // Initialisation du système de fichiers ROM
    romfsInit();
    chdir("romfs:/");
    
    // Initialisation des structures de jeu
    GameState gameState;
    gameState.window = NULL;
    gameState.renderer = NULL;
    gameState.joystick = NULL;
    gameState.currentPage = PAGE_ACCUEIL;
    gameState.running = 1;
    
    for (int i = 0; i < MAX_IMAGES; i++) {
        gameState.textures[i] = NULL;
    }
    
    // État du pad
    PadState pad;
    u64 kDown;
    
    // Création du personnage
    Character character = {0};
    
    // Initialiser les sous-systèmes
    initializeInput(&pad);
    if (!initializeGraphics(&gameState)) {
        printf("Erreur d'initialisation graphique\n");
        goto cleanup;
    }
    
    if (!initializeAudio()) {
        printf("Erreur d'initialisation audio\n");
        // On continue même si l'audio échoue
    }
    
    if (!initializeVibration()) {
        printf("Erreur d'initialisation des vibrations\n");
        // On continue même si la vibration échoue
    }
    
    // Initialiser le personnage
    if (!initializeCharacter(&gameState, &character)) {
        printf("Erreur d'initialisation du personnage\n");
        // On continue même si l'initialisation du personnage échoue
    }
    
    // Ouvrir le joystick
    gameState.joystick = SDL_JoystickOpen(0);
    
    // Boucle principale
    while (gameState.running && appletMainLoop()) {
        
        // Traiter les entrées
        processInput(&pad, &gameState, &kDown);
        
        // Mettre à jour les vibrations
        updateVibration();
        
        // Mettre à jour le personnage
        updateCharacter(&gameState, &character, &pad);
        
        // Afficher le contenu
        renderFrame(&gameState);
        
        // Afficher le personnage
        renderCharacter(&gameState, &character);
        
        // Présenter le rendu mis à jour
        SDL_RenderPresent(gameState.renderer);
        
        // Limiter le frame rate
        SDL_Delay(16); // ~60 FPS
    }
    
cleanup:
    // Arrêter la vibration avant de quitter
    stopVibration(&pad);
    
    // Nettoyer les ressources
    cleanupGraphics(&gameState);
    cleanupAudio();
    cleanupVibration();
    cleanupInput(gameState.joystick);
    cleanupCharacter(&character);
    
    // Fermeture de romfs
    romfsExit();
    
    return 0;
}