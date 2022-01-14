#include "OBP60Timer.h"

// actually not a real regatta timer, only a time counter without utility, must be expanded
void printTimer(busData *bInfo)  // Start Timer
{   
	static unsigned long time0=millis();
  unsigned long timeBegin=millis();
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 80);
    display.print("Timer");
  
    // measurements
    display.setFont(&DSEG7Classic_BoldItalic42pt7b);
    display.setCursor(20, 200);
    int sec;
    int min;
    int hour;
    unsigned long t;
    t=millis();
    hour = (t-time0)/(1000*3600);
    t=t-hour*1000*3600;
    min = (t-time0)/(1000*60);
    t=t-min*1000*60;
    sec=(t-time0)/1000;
    if(hour<1)
    {

    }
    if(hour>0 && hour<10)
    {
      display.print(" ");
      display.print(hour);
      display.print(":");
    }
    if(hour>=10)
    {
      display.print(hour);
      display.print(":");
    }

    if(min>=0 && min<10)
    {
      display.print(" ");
      display.print(min);
      display.print(":");
    }
    if(min>=10)
    {
      display.print(min);
      display.print(":");
    }
    
    if(sec>=0 && sec<10)
    {
      display.print("0");
      display.print(sec);
    }
    if(sec>=10)
    {
      display.print(sec);
    }
    unsigned long timeEnd=millis();
    // debug write time in function
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(200, 80);
    display.print(timeAfter-timeBefore);
}