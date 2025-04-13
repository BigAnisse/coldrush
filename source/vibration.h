#ifndef VIBRATION_H
#define VIBRATION_H

#include <switch.h>

// Fonctions de gestion des vibrations
int initializeVibration();
void activateVibration(PadState* pad);
void updateVibration();
void stopVibration(PadState* pad);
void cleanupVibration();

#endif // VIBRATION_H