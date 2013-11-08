#include "globals.h"

extern volatile char    packet1, packetX, packetY;
extern volatile int     mouseDataReady;
extern volatile int     mouseDataProcessing;
extern volatile struct  mouse_dev   mouse;


/***************************************************************************************
 * Pushbutton - Interrupt Service Routine                                
 *                                                                          
 * This routine checks which KEY has been pressed. If it is KEY1 or KEY2, it writes this 
 * value to the global variable key_pressed. If it is KEY3 then it loads the SW switch 
 * values and stores in the variable pattern
****************************************************************************************/
void PS2_ISR( void )
{
	static char byteCount = 0;
  	volatile int * PS2_ptr = (int *) 0x10000100;		// PS/2 port address
	int PS2_data, RVALID;

	PS2_data = *(PS2_ptr);					// read the Data register in the PS/2 port
	RVALID = (PS2_data & 0x8000);			// extract the RVALID field
	if (RVALID)
	{
        if(byteCount == 0)
        {
            mouseDataReady = 0;
            byteCount++;
            packet1 = PS2_data & 0xFF;
        }
        else if(byteCount == 1)
        {
            mouseDataReady = 0;
            byteCount++;
            packetX = PS2_data & 0xFF;
        }
        else if(byteCount == 2)
        {
            byteCount = 0;
            packetY = PS2_data & 0xFF;
            if(mouseDataProcessing == 0)
            {
                //change struct here
                if((packet1 & 1<<4 )!= 0)
                {
                    packetX = packetX - 256;
                }
                if((packet1 & 1<<5) != 0)
                {
                    packetY = packetY - 256;
                }
                mouse.deltaX = packetX;
                mouse.deltaY = packetY;
                mouse.buttons = packet1 & 0x7;
                mouseDataReady = 1;
            }
        }
	}
	return;
}
