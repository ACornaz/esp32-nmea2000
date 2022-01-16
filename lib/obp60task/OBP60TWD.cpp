#include "OBP60TWD.h"


void printTWD(busData *bInfo)  // Graphic Page for TWD last 10 min
{   // test phase only dummy array
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 80);
    display.print("TWD");
  
    // measurements
	display.fillRect(198, 20, 3, 260, GxEPD_BLACK);   // Vertical line 3 pix
	for(int i=0;i<260;i++)
	{
        int16_t x;
		int16_t y;
		x=(int16_t) (199 + 50*sin((double)i*2*pi/50.0));
		y=20+i;
		display.drawRect(x,y,3,3,GxEPD_BLACK);
	}
 
}