#include "InterruptHandler.h"
#include "GameModes.h"
#include <Arduino.h>

const unsigned int D2_PORT = 1;
const unsigned int D2_PIN = 4;

unsigned int getNextCPUINT(unsigned int start) {
  /* Get next unused CPU interrupt > start */
  unsigned int tryInt = start + 1;
  while (tryInt < 32) {
    if (NVIC_GetEnableIRQ((IRQn_Type)tryInt) == 0) {
      return tryInt;
    }
    tryInt++;
  }
}

const unsigned int CPU_INT_1 = getNextCPUINT(1);

void ourISR() {
  static int timesPushed = 0; 
  Serial.println(timesPushed++);
  if (R_ICU->IELSR_b[CPU_INT_1].IR == 1) {
   // brightNormal = !brightNormal; //toggle brightness mode on interrupt
    currentMode = static_cast<GameMode>((currentMode + 1) % MODE_COUNT);
    Serial.println(currentMode);
    // comment out if/else to make it pause and unpause instead of on/off
    // if (brightNormal) {
    //    matrix.fillScreen(0);  // Turn on the matrix (clear screen)
    //    matrix.show();         // Update the matrix display
    // } else {
    //    matrix.clear();        // Turn off the matrix
    //    matrix.show();         // Update the matrix display
    // }
    R_ICU->IELSR_b[CPU_INT_1].IR = 0;
    NVIC_ClearPendingIRQ((IRQn_Type)CPU_INT_1);
  }
}

void interruptSetup() {
  // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1;
  // R_PFS->PORT[D6_PORT].PIN[D6_PIN].PmnPFS_b.PDR = 1; // Set as output
  R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS_b.PDR = 0;

  // Disable the CPU interrupt while we configure it
  NVIC_DisableIRQ((IRQn_Type)CPU_INT_1);

  // TODO: Configure D2 as an input AND to be used as an IRQ input pin
  R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS = (1 << R_PFS_PORT_PIN_PmnPFS_ISEL_Pos);

  // TODO: Trigger an interrupt when D2 goes from LOW to HIGH (prelab Q4.6)
  // Configure the ICU to connect the Port IRQ to the CPU (NVIC) IRQ (prelab Q4.7)
  R_ICU->IELSR[CPU_INT_1] = 0x002;

  // Use the Arm CMSIS API to enable *CPU* interrupts
  NVIC_SetVector((IRQn_Type)CPU_INT_1, (uint32_t)&ourISR);  // set vector entry to our handler
  NVIC_SetPriority((IRQn_Type)CPU_INT_1, 14);               // Priority lower than Serial (12)
  NVIC_EnableIRQ((IRQn_Type)CPU_INT_1);
}