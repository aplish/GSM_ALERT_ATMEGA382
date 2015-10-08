//Program for 8052 Microcontroller

#include<regx51.h>
#include<stdio.h>
#include<lcd.h>
#include<serial.h>

#define ENGINE P1_0
#define HIDSW  P1_1

unsigned int x,y;
void delayms(unsigned int ms)
{
	for(x=0;x<ms;x++)
	{
		for(y=0;y<1275;y++);
	}
}


void main()
{
	P1=0x00;
	P2=0x00;
	SerialInput();
	InitLCD();
	EA=1;
	ES=1;
	EX1=1;
	
	while(1)
	{
		ClearLCDScreen();
		WriteStringToLCD("IDLE");
		delayms(100);
	}
}



void Majorfirst_ISR(void) interrupt 2
{
	SerialTransmit();
}


void Major_ISR(void) interrupt 4
{

 	if(TI==1&&RI==1)
      {
         RI=0;
         TI=0;
      }

  else if(TI==1)

       { 

        if(HIDSW==1&&ENGINE==1)

	       {
	printf("AT+CMGF=1%c",13);
	delayms(100);
	
	printf("AT+CMGS=\"9625459453\"%c",13);
	delayms(50);
	
    ClearLCDScreen();
	
	WriteStringToLCD("Sending message..");
	
	printf("UNAUTHORIZED ACCESS!! TO STOP THE ENGINE REPLY 'Y'");
	printf("%c", 0x1A);
	
		delayms(100);

		ClearLCDScreen();
		WriteStringToLCD("Message sent!");
	
		TI=0;
	}
      

else if(HIDSW==0&&ENGINE==1)
        {
                while(1)
	       {
		ClearLCDScreen();
		WriteStringToLCD("OWNER ACCESS");
		delayms(100);
	       }


        }
				
				 else
          { 
                while(1)
	{
		ClearLCDScreen();
		WriteStringToLCD("SYSTEM NOT FUNCTIONAL");
		delayms(100);
	}
           }
}


	
	else
		
	{
	
       char sms;
	
		
	printf("AT+CMGF=1%c",13);
	delayms(100);
	printf("AT+CMGR=1%c",13);
	delayms(50);

	while(RI==0); //ready to receive
		
		sms=SBUF;
		RI=0;
		
	

ENGINE=0;
		ClearLCDScreen();
		WriteStringToLCD("ENGINE STOPPED!");
		
		}
}
