#include "OBP60Dummy.h"


void printDummy(busData *bInfo, String *kAction)  // Dummy Page displayed if no pages are selected 
{   
  	display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
	display.drawExampleBitmap(gImage_Logo_OBP_400x300_sw, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE); // Draw start logo
    topMargin.print(bInfo);
  	buttomStatusLine("clean","nop","nop");
	display.setFont(&Ubuntu_Bold8pt7b);
    display.setTextColor(GxEPD_BLACK);
	display.setCursor(40,260);
	display.print("Program the Pages with WIFI-Interface");
	display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);
	if(*kAction=="2s"){
		display.update();
		*kAction="0";
	}
}
