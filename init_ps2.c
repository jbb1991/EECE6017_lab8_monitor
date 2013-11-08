#include "globals.h"
extern volatile int *PS2_ptr;

int init_ps2(void)
{
    char PS2_data;
	*(PS2_ptr) = 0xFF; 				/* reset */
    PS2_data = (*PS2_ptr)&(char)0xFF;

    // Wait for an ACK
    while(PS2_data != 0xFA) {
        PS2_data = (*PS2_ptr)&(char)0xFF;
    }

    // Wait for a response from the BAT. 0xAA means OK, 0xFC means error
    while(PS2_data != 0xAA || PS2_data != 0xFC) {
        PS2_data = (*PS2_ptr)&(char)0xFF;
    }
    if(PS2_data == (char)0xFC)
        return -1;

    // Wait until the mouse ID is received
    while(*(PS2_ptr) == PS2_data) {
        
    }
    PS2_data = (*PS2_ptr)&(char)0xFF;

    // ID == 0x03, scrollwheel mouse with 4 byte packet.
    // we do not support this
    else if(PS2_data == (char)0x03) {
        return -1;
    }

    // Enable reporting of new data
    (*PS2_ptr) = 0xF4;

    // Wait for an ACK
    while(PS2_data != 0xFA) {
        PS2_data = (*PS2_ptr)&(char)0xFF;
    }

    // Write to the PS/2 Control register to enable interrupts
	*(PS2_ptr + 1) = 0x1;
}
