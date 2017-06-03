#include <stdio.h>
#include <stdlib.h>
#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
#include "mscan.h"
#include "car_controller.h"
#include "bit_fiddling.h"
#include "utils.h"

volatile int floor = 0;
int led = 0;
int retCode = 1;
unsigned char floorSelected = FALSE;
CANmsg_t rxMsg;
unsigned char rxdata[8];
unsigned char txdata[8];

// Delay_ms()
// wait for specified # of ms, then return
// uses channel 0 of the timer module in polling mode
void 
Delay_ms( word delayTime ) 
{
   	
    // initialize the timer module - set prescaler and enable
    SET_TCNT_PRESCALE( TCNT_PRESCALE_64 );
    TSCR1 = TSCR1_INIT;

 	// configure timer channel 0 as OC, no output pin action, prime for 1ms initial delay
    MAKE_CHNL_OC( 0 );
    SET_OC_ACTION( 0, OC_OFF );  	
    TC0 = TCNT + OC_1MS_DELAY;
    
	
	// loop for the specified # of ms
	while (delayTime--) {
		while( BIT_IS_CLR( TFLG1, TFLG1_C0F_MASK ) );
        TC0 += OC_1MS_DELAY;                         // rearm the OC register for the next delay - clears TFLG1
   	}

} // Delay_ms()

/*
/ Function: Init_Car_Controller()
/ Input: Void
/ Output: Void
/ Purpose: Initializes the DDR and ports required to enable buttons and LEDs associated with the 
/          car controller.
*/
/*void
Init_CAN_Msg(CANmsg_t msgPtr)
{
  int index = 0;
  msgPtr->id = CC_CAN_ID;
  msgPtr->length = 8;
  msgPtr->rtr = 0;
  msgPtr->priority = 0;
  msgPtr->txdata = 0;
} */

/*
/ Function: Init_Car_Controller()
/ Input: Void
/ Output: Void
/ Purpose: Initializes the DDR and ports required to enable buttons and LEDs associated with the 
/          car controller.
*/
void 
Init_Car_Controller()
{
  // configure button DDR
  // configure PTAD to PIM module/as a GPIO
  SET_BITS(ATDDIEN, PTAD_AS_GPIO_MASK);
  //configure digital input for limit switches  
  DDRAD   = DDRAD_INIT;      
   
  // configure floor request LED port data direction to output
  SET_BITS(LED_PORT_DDR, DOOR_LEDS_ON);
  // turn on both LEDs
  SET_BITS(LED_PORT,DOOR_LEDS_ON);
  Delay_ms(1000);
  // turn off both LEDs
  CLR_BITS(LED_PORT, DOOR_LEDS_OFF);
  
  // configure floor request LEDs DDR to output
  SET_BITS(FLOOR_REQ_LEDS_DDR, DDRB_OUTPUT);
  // turn on red LEDs for 1 second
  SET_BITS(FLOOR_REQ_LEDS_PORT, LEDS_ON);
  Delay_ms(1000);
  // turn off red LEDs
  CLR_BITS(FLOOR_REQ_LEDS_PORT, LEDS_OFF);
  
  // configure floor status LED DDR to output
  SET_BITS(FLOOR_STATUS_LEDS_DDR, DDRA_OUTPUT);
  // turn on green LEDs for 1 second
  SET_BITS(FLOOR_STATUS_LEDS_PORT, LEDS_ON);
  Delay_ms(1000);
  // turn off green LEDs
  CLR_BITS(FLOOR_STATUS_LEDS_PORT, LEDS_OFF);
}

void 
main()
{
  Init_Car_Controller();
  MSCAN_Init();
  MSCAN_ListenForMsg(EC_CAN_ID, 0);
  txdata[7] |= 0x05;
  for(;;)
  {   
   // poll for valid message flag
   while(!MSCAN_GotMsg());
   // if valid message, read message
   MSCAN_Getd(&rxMsg);
   
  // check for message from elevator controller 
  if(rxMsg.id == EC_CAN_ID)
  {
    // reset id for next message
    rxMsg.id = 0;
  } 
  else
  {
    // we have invalid message filter
   floor =0; 
  }

  // poll for a valid floor selection
  while(!floorSelected)
  {
   switch(READ_CAR_FLOOR_REQ)
   {
    case FLOOR_1:
      txdata[7] |= FLOOR_1;
      floorSelected = TRUE;
      break;
   
    case FLOOR_2:
      txdata[7] |= FLOOR_2;
      floorSelected = TRUE;
      break;
      
    case FLOOR_3:
      txdata[7] |= FLOOR_3;
      floorSelected = TRUE;
      break;
    
    default:
      txdata[7] |= FLOOR_NONE;
      break;
   }
  }
 
  }
}
