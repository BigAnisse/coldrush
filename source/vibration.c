#include "vibration.h"
#include "common.h"

// Variables globales pour la vibration
static HidVibrationDeviceHandle VibrationDeviceHandles[2][2];
static HidVibrationValue VibrationValue;
static HidVibrationValue VibrationValue_stop;
static int vibration_frames = 0;
static u32 target_device = 0;

int initializeVibration() {
    Result rc = 0;
    
    // Initialize vibration devices for both handheld and Joy-Con controllers
    rc = hidInitializeVibrationDevices(VibrationDeviceHandles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    if (R_SUCCEEDED(rc)) rc = hidInitializeVibrationDevices(VibrationDeviceHandles[1], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);

    // Set vibration values
    VibrationValue.amp_low = 0.5f;   // Amplitude plus forte pour une meilleure sensation
    VibrationValue.freq_low = 160.0f; // Fréquence plus haute pour une vibration plus nette
    VibrationValue.amp_high = 0.5f;
    VibrationValue.freq_high = 320.0f;

    memset(&VibrationValue_stop, 0, sizeof(HidVibrationValue));
    VibrationValue_stop.freq_low = 160.0f;
    VibrationValue_stop.freq_high = 320.0f;
    
    return R_SUCCEEDED(rc);
}

void activateVibration(PadState* pad) {
    // Sélectionner quel appareil doit vibrer
    target_device = padIsHandheld(pad) ? 0 : 1;
    hidSendVibrationValues(VibrationDeviceHandles[target_device], &VibrationValue, 1);
    vibration_frames = VIBRATION_DURATION;
}

void updateVibration() {
    // Gestion de la durée de vibration
    if (vibration_frames > 0) {
        vibration_frames--;
        
        // Si la vibration vient de se terminer, l'arrêter
        if (vibration_frames == 0) {
            hidSendVibrationValues(VibrationDeviceHandles[target_device], &VibrationValue_stop, 1);
        }
    }
}

void stopVibration(PadState* pad) {
    // Sélectionner quel appareil doit vibrer
    target_device = padIsHandheld(pad) ? 0 : 1;
    hidSendVibrationValues(VibrationDeviceHandles[target_device], &VibrationValue_stop, 1);
    vibration_frames = 0;
}

void cleanupVibration() {
    // Rien à nettoyer pour la vibration
}