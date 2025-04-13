#include "audio.h"
#include "common.h"

// Variables globales pour l'audio
static Mix_Music *music = NULL;
static Mix_Chunk *sound_effect = NULL;

int initializeAudio() {
    // Initialisation de l'audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
        printf("Erreur d'initialisation de l'audio: %s\n", Mix_GetError());
        return 0;
    }
    
    // Allouer plusieurs canaux pour les effets sonores
    Mix_AllocateChannels(8);
    
    // Charger la musique de fond
    music = Mix_LoadMUS("data/background.ogg");
    if (music) {
        Mix_PlayMusic(music, -1); // Jouer en boucle
        printf("Musique de fond chargée et démarrée.\n");
    } else {
        printf("Erreur lors du chargement de la musique de fond: %s\n", Mix_GetError());
    }

    // Charger l'effet sonore pour le bouton A
    sound_effect = Mix_LoadWAV("data/test.mp3");
    if (!sound_effect) {
        printf("Erreur lors du chargement de l'effet sonore: %s\n", Mix_GetError());
        // Tentative alternative avec un autre format
        sound_effect = Mix_LoadWAV("data/test.wav");
        if (!sound_effect) {
            printf("Deuxième tentative échouée: %s\n", Mix_GetError());
            return 0;
        }
    } else {
        printf("Effet sonore chargé avec succès.\n");
        // Régler le volume de l'effet sonore
        Mix_VolumeChunk(sound_effect, MIX_MAX_VOLUME);
    }
    
    return 1;
}

void playButtonSound() {
    if (sound_effect) {
        // Jouer sur un canal spécifique pour ne pas interférer avec la musique
        Mix_PlayChannel(SFX_CHANNEL, sound_effect, 0); // 0 = ne pas répéter
        printf("Effet sonore joué sur le canal %d\n", SFX_CHANNEL);
    } else {
        printf("Effet sonore non disponible\n");
    }
}

void cleanupAudio() {
    // Libérer les ressources audio
    if (music)
        Mix_FreeMusic(music);
    if (sound_effect)
        Mix_FreeChunk(sound_effect);
    Mix_CloseAudio();
}