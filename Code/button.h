
#ifndef __BUTTON_H__
#define __BUTTON_H__

#define BUTTON1   0x01
#define BUTTON2   0x02
#define BUTTON3   0x04
#define BUTTON4   0x08

#include "44b.h"

unsigned int State_Button(void);
int Push_Button(void);

#endif