#include "OBP60TWD.h"


void printTWD(busData *bInfo, String *kAction)  // Graphic Page for TWD last 10 min
{   // test phase only dummy array
  	display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  	topMargin.print(bInfo);
  	if(*kAction=="2s"){
		display.update();
		*kAction="0";
	}
	if(*kAction=="3s"){
		*kAction="0";
	}
	if(*kAction=="4s"){
		display.update();
		*kAction="0";
	}
    // title
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 50);
    display.print("TWD");
	
	// measurements
	display.setCursor(320, 50);
    display.print(bInfo->TWD.svalue);
	display.setCursor(320, 90);
	display.print("deg");

    // graphic TWD
	display.fillRect(198, 20, 3, 260, GxEPD_BLACK);   //  actual wind direction vertical line 3 pix
	// minutes tix
	display.setFont(&Ubuntu_Bold8pt7b);
    display.setTextColor(GxEPD_BLACK);
  
	for(int i=0;i<4;i++)
	{
		display.fillRect(195, 20+i*60-1, 10, 3, GxEPD_BLACK); //  min tix
		display.setCursor(150,25+i*60-1);
		display.print(i);
		display.print(" min");
	}
	// deg tix
	int factor=5;
	for(int i=-3;i<4;i++)
	{	
    	display.fillRect(199+i*factor*10-1, 250, 3, 10, GxEPD_BLACK); // 10 deg tix
		display.setCursor(199+i*factor*10-10,275);
		display.print(10*i);
	}

	for(int i=0;i<300;i++)
	{
        int16_t x;
		int16_t y;
		int16_t dx= (int16_t)(bInfo->TWDarray[i][1] - bInfo->TWDarray[0][1]);
		if(dx<-180) dx=dx+360;
		if(dx>180) dx=dx-360;
		x = 199 + dx ;
		y = 20  -( (int16_t)(bInfo->TWDarray[i][0]/1000.0) - (int16_t)(bInfo->TWDarray[0][0]/1000.0));
		display.drawRect(x-1,y-1,3,3,GxEPD_BLACK);
	}
 
}