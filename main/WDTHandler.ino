#include "WDTHandler.h"
#include "WDT.h"

void WDTSetup() {
    if (WDT.begin(5000)) {
        WDT.refresh();
    }
}

void petWDT() {
    WDT.refresh();
    lastPetTime = millis(); 
}