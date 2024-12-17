#include "SoundProcessor.h"
#include <Arduino.h>
#include "Globals.h"

int sound_sensor = A0;
int pass = 0;

void soundProcessorSetup() {
    pinMode(sound_sensor, INPUT);
}

int pollSound() {
    int soundValue = 0;                     
    for (int i = 0; i < 32; i++)  
    { soundValue += analogRead(sound_sensor); } 

    soundValue >>= 5;            //bitshift operation

    if (soundValue > 250) {
      if (pass < 20) {
        soundValues[pass] = soundValue;
        pass += 1;
      } else {
        pass = 0;
      }
      if (filled < 20) {
        filled += 1;
      }
    }

    return soundValue;
}
