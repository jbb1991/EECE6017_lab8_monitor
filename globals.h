#ifndef GLOBALS_H
#define GLOBALS_H 1

#define BUF_SIZE 500000			// about 10 seconds of buffer (@ 48K samples/sec)
#define BUF_THRESHOLD 96		// 75% of 128 word buffer
#define KB_BUF_SIZE 256        // Maximum size of the keyboard buffer


#define LMB 1
#define MMB 2
#define RMB 4

struct mouse_dev {
    int deltaX;
    int deltaY;
    int buttons;
};

#endif //GLOBALS_H
