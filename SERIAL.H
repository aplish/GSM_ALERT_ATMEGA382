//SERIAL.H 

#ifndef __SERIAL_H
#define __SERIAL_H

void SerialTransmit(void);
void SerialInput(void);
void SerialTransmit(void)

{

   SCON = 0x50;                        /* SCON: mode 1, 8-bit UART, enable rcvr        */

   TMOD = 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload                   */

   TH1   = 0xFD;               /* TH1: reload value for 9600 baud @ 11.0592MHz*/

   TR1   = 1;                 /* TR1: timer 1 run                             */

   TI   = 1;                 /* TI:   set TI to send first char of UART          */

}


void SerialInput(void)		           // INITIALIZE SERIAL PORT
{
	TMOD = 0x20;	                       // Timer 1 IN MODE 2 -AUTO RELOAD TO GENERATE BAUD RATE
	SCON = 0x50;			               // SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED 
	TH1 = 0xfd;		               // LOAD BAUDRATE TO TIMER REGISTER
	TR1 = 1;			                   // START TIMER
}

#endif

