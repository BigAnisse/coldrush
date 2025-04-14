#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <switch.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "common.h"
#include "input.h"
#include "graphics.h"
#include "audio.h"
#include "vibration.h"
#include "character.h" // Nouvel include

 
// Fonction principale
int main(int argc, char** argv);

#endif // MAIN_H