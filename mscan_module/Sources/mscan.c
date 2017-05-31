#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
#include "mscan.h"
#include "bit_fiddling.h"



void 
MSCAN_Init(void){
  // assert CANE - MSCAN module turn on
  SET_BITS(CANCTL1, CANCTL1_CANE_MASK);
  // request for MSCAN init mode
  SET_BITS(CANCTL0, CANCTL0_INITRQ_MASK);

  // wait for MSCAN module to enter init mode, checking for acknowledgement flag
  while((BIT_IS_CLR(CANCTL1, CANCTL1_INITAK_MASK)));

  // successfully entered init mode
  // configuring registers to control MSCAN operation

  CANCTL1 = CANCTL1_INIT;
  CANBTR0 = CANBTR0_INIT;
  CANBTR1 = CANBTR1_INIT;
    
  // exit init mode and enter normal operation
  CLR_BITS(CANCTL0, CANCTL0_INITRQ_MASK);
  // wait for module to exit init mode
  while((BIT_IS_SET(CANCTL1, CANCTL1_INITAK_MASK)));
}

void
MSCAN_ListenForMsg(unsigned long id, unsigned rtr)
{
  unsigned long myId;

  // assert CANE - MSCAN module turn on
  SET_BITS(CANCTL1, CANCTL1_CANE_MASK);
  // request for MSCAN init mode
  SET_BITS(CANCTL0, CANCTL0_INITRQ_MASK);

  // wait for MSCAN module to enter init mode, checking for acknowledgement flag
  while((BIT_IS_CLR(CANCTL1, CANCTL1_INITAK_MASK)));

  // setup acceptance filter registers
  // setup four 16-bit acceptance filters
  CANIDAC = CANIDAC_INIT;
  
  // filter 0
  myId =  


}


