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
const unsigned int WDT_INT = getNextCPUINT(CPU_INT_1);

void ourISR() {
  static int timesPushed = 0; 
  Serial.println(timesPushed++);
  if (R_ICU->IELSR_b[CPU_INT_1].IR == 1) {
    currentMode = static_cast<GameMode>((currentMode + 1) % MODE_COUNT);
    Serial.println(currentMode);
    R_ICU->IELSR_b[CPU_INT_1].IR = 0;
    NVIC_ClearPendingIRQ((IRQn_Type)CPU_INT_1);
  }
}

void interruptSetup() {
  R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS_b.PDR = 0;

  // Disable the CPU interrupt while we configure it
  NVIC_DisableIRQ((IRQn_Type)CPU_INT_1);

  // Configure D2 as an input AND to be used as an IRQ input pin
  R_PFS->PORT[D2_PORT].PIN[D2_PIN].PmnPFS = (1 << R_PFS_PORT_PIN_PmnPFS_ISEL_Pos);

  // TODO: Trigger an interrupt when D2 goes from LOW to HIGH (prelab Q4.6)
  R_ICU->IRQCR[CPU_INT_1] = 0b01;
  // Configure the ICU to connect the Port IRQ to the CPU (NVIC) IRQ (prelab Q4.7)
  R_ICU->IELSR[CPU_INT_1] = 0x002;

  // Use the Arm CMSIS API to enable *CPU* interrupts
  NVIC_SetVector((IRQn_Type)CPU_INT_1, (uint32_t)&ourISR);  // set vector entry to our handler
  NVIC_SetPriority((IRQn_Type)CPU_INT_1, 14);               // Priority lower than Serial (12)
  NVIC_EnableIRQ((IRQn_Type)CPU_INT_1);
}