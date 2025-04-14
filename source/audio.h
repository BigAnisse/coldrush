#ifndef AUDIO_H
#define AUDIO_H
#define SFX_CHANNEL -1  // -1 = laisse SDL choisir un canal libre

#include <SDL_mixer.h>

// Fonctions de gestion audio
int initializeAudio();
void playButtonSound();
void cleanupAudio();

#endif // AUDIO_H