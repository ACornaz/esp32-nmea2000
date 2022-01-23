#include "OBP60Timer.h"

// actually not a real regatta timer, only a time counter without utility, must be expanded
void printTimer(busData *bInfo, String *kAction)  // Start Timer
{   
  enum timerStatus {stopped, started}; 
  static long startMinutes=5;
	static long time0=(long)millis();
  unsigned long timeBegin=millis();
  static timerStatus tStatus=stopped;
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen

  topMargin.print(bInfo);
  if(tStatus==stopped){  // timer is stopped
    buttomStatusLine("start","reset","");
    if(*kAction=="2s"){
      time0=(long)millis()+startMinutes*60000;
      display.fillRect(60, 270, 150, 30, GxEPD_WHITE);   // Draw white sreen
      tStatus=started;
		  *kAction="0";
	  }
	  if(*kAction=="3s"){
		  *kAction="0";
	  }
	  if(*kAction=="4s"){
		  *kAction="0";
	  }
  }
  if(tStatus==started){
    buttomStatusLine("stop","synchr","");
    if(*kAction=="2s"){
      tStatus=stopped;
		  *kAction="0";
	  }
	  if(*kAction=="3s"){
		  *kAction="0";
	  }
	  if(*kAction=="4s"){
		  display.update();
		  *kAction="0";
	  }
  }

    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 80);
    display.print("Regatta Timer");
  
    // measurements
    display.setFont(&DSEG7Classic_BoldItalic42pt7b);
    display.setCursor(20, 200);
    long sec;
    long min;
    long hour;
    long t;
    if(tStatus==started)
        t=(long)(millis());
    if(tStatus==stopped)
        t=time0-startMinutes*60000;
    long dt=(time0-t);
    hour = dt/(1000*3600);
    dt=dt-hour*1000*3600;
    min = dt/(1000*60);
    dt=dt-min*1000*60;
    sec=dt/1000;
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
    display.setCursor(300, 80);
   // display.print(timeAfter-timeBefore);
}