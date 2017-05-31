#ifndef _MSCAN_H
#define _MSCAN_H
  

/*CANTCL1 register*
  Turn on MSCAN module
  Init mode request to enter init mode
  Enable bus clock = 8MHz*/
#define CANCTL1_INIT (CANCTL1_CANE_MASK | CANCTL1_CLKSRC_MASK)

/*CANBTR0 register
  CAN synchronization jump width = 1
  CAN prescaler value = 8*/
#define CANBTR0_INIT            0x07

/*CANBTR1 register
  CAN time segment 1 value = 4
  CAN time segment 2 value = 3
  CAN Tq = 1*/
#define CANBTR1_INIT            0x23

/*CANIDAC register*/
#define CANIDAC_INIT            0x10

#define NO_ERR                  0 

#define ERR_BUFFER_FULL         1

/*Acceptance filter*/
CANIDAR0 


typedef struct msgFrame
{
  unsigned long id;
  unsigned char length;
  unsigned char *txdata;
}*CANmsg_t;


extern void MSCAN_Init(void);
#endif