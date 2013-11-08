#include "globals.h"
extern volatile int *PS2_ptr;

int init_ps2(void)
{
    char PS2_data;
	*(PS2_ptr) = 0xFF; 				/* reset */
    PS2_data = (*PS2_ptr)&(char)0xFF;
    while(PS2_data != 0xAA || PS2_data != 0xFC)
    {
        PS2_data = (*PS2_ptr)&(char)0xFF;
    }
    if(PS2_data == (char)0xFC)
        return -1;

	*(PS2_ptr + 1) = 0x1; 			/* write to the PS/2 Control register to enable interrupts */

}
