#ifndef _CAR_CONTROLLER_H
#define _CAR_CONTROLLER_H

#define READ_CAR_FLOOR_REQ (PTAD & 0x07)

#define PTAD_AS_GPIO_MASK 0x07
#define DDRAD_INIT  0x00

#define LED_PORT_DDR DDRS
#define LED_PORT  PTS
#define LEDS_ON (PTS_PTS2_MASK | PTS_PTS3_MASK)
#define LEDS_OFF (PTS_PTS2_MASK | PTS_PTS3_MASK)
#define LED_1_ON  PTS_PTS2_MASK
#define LED_2_ON  PTS_PTS3_MASK

#define FLOOR_REQ_LEDS_DDR  DDRB
#define FLOOR_REQ_LEDS_PORT PORTB
#define DDRB_OUTPUT         0x07
#define FLOOR_LED_1         PORTB_BIT0_MASK
#define FLOOR_LED_2         PORTB_BIT1_MASK
#define FLOOR_LED_3         PORTB_BIT2_MASK
#define FLOOR_REQ_LEDS_ON   0x07
#define FLOOR_REQ_LEDS_OFF  0x07
 

#define DOOR_STATE_OPEN 0x00
#define DOOR_STATE_CLOSE 0x01
#define CURRENT_DOOR_STATE 0x00

#define FLOOR_NONE 0x00
#define FLOOR_1    0x01
#define FLOOR_2    0x02  
#define FLOOR_3    0x04

#define CC_CAN_ID  0x200
#define EC_CAN_ID  0x101

#define RTR_VALUE  0

extern void Init_Car_Controller(void);
extern void Write_C_LED(int led);

#endif