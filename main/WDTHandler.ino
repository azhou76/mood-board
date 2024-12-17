#include "WDTHandler.h"
#include "InterruptHandler.h"


void WDTSetup() {

  // set frequency of watchdog to be 3kHz using CKS, set timeout period to be ~5 seconds using TOPS, set that the watchdog can be refreshed any time during the window using RPSS and RPES
  R_WDT->WDTCR = (0b1000 << R_WDT_WDTCR_CKS_Pos) | (0b11 << R_WDT_WDTCR_TOPS_Pos) | (0b11 << R_WDT_WDTCR_RPSS_Pos) | (0b11 << R_WDT_WDTCR_RPES_Pos);

  // Enable WDT when debugger is connected
  R_DEBUG->DBGSTOPCR_b.DBGSTOP_WDT = 0;
  R_WDT->WDTSR = 0; // clear watchdog status;

  // connect ICU to CPU and indicate watchdog handler
  R_WDT->WDTRCR= (1 << 7);
  R_ICU->IELSR[WDT_INT] = (0x025 << R_ICU_IELSR_IELS_Pos);

  NVIC_SetVector((IRQn_Type) WDT_INT, (uint32_t) &wdtISR);
  NVIC_SetPriority((IRQn_Type) WDT_INT, 14);
  NVIC_EnableIRQ((IRQn_Type) WDT_INT);

}

void petWDT() {
  R_WDT->WDTRR = 0x00;
  R_WDT->WDTRR = 0xFF;
}

/* ISR when WDT is triggered */
void wdtISR() {
  Serial.println("WOOF!!!");
  NVIC_SystemReset();
}
