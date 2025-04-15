#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

// Fonctions de gestion audio
int initializeAudio();
void playButtonSound();
void cleanupAudio();

#endif // AUDIO_H