// polling et pas interruption

#include "44b.h"
#include "button.h"

unsigned int State_Button(void)
   {
   rPCONG=0x0;  //IN7~0
   rPUPG=0x0;     //pull up enable
   return ~((rPDATG&0xf0)>>4);
   /*
             B4 B3 B2 B1
    rPDATG ([x][x][x][x][x][x][x][x]) & 0xF0 ([1][1][1][1][0][0][0][0])= [x][x][x][x][0][0][0][0]
     >> 4 = [0][0][0][0][x][x][x][x] 
            [0][0][0][0][x][x][x][x] & 0x01 = [0][0][0][0][0][0][0][x]
            [0][0][0][0][x][x][x][x] & 0x02 = [0][0][0][0][0][0][x][0]
            [0][0][0][0][x][x][x][x] & 0x04 = [0][0][0][0][0][x][0][0]
            [0][0][0][0][x][x][x][x] & 0x08 = [0][0][0][0][x][0][0][0]
   */
   }

int Push_Button(void)
{ 
    unsigned int StateB = State_Button();
    if((StateB & BUTTON1)==1) 
    	{          
    	  return 1;
      }	        
    	
    if((StateB & BUTTON2)==2) 
    	{
    	   return 2;
    	}	        
    	
    if((StateB & BUTTON3)==4) 
    	{
    	   return 3;
    	}	        
    	
    if((StateB & BUTTON4)==8) 
    	{
    	   return 4;
    	}
}
