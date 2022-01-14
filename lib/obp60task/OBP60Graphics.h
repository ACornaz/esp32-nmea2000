#ifndef _OBP60_GRAPHICS_H
#define _OBP60_GRAPHICS_H

#include <arduino.h> // is needed for some defintions eg byte ...

#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" Waveshare S/W 300 x 400 pixel

#include "Ubuntu_Bold8pt7b.h"
#include "Ubuntu_Bold20pt7b.h"
#include "Ubuntu_Bold32pt7b.h"
#include "DSEG7Classic-BoldItalic16pt7b.h"
#include "DSEG7Classic-BoldItalic30pt7b.h"
#include "DSEG7Classic-BoldItalic42pt7b.h"
#include "DSEG7Classic-BoldItalic60pt7b.h"
//#include "FreeMonoBold9pt7b.h"
#include "Seven_Segment32pt7b.h"   // need in OBP60Graphics.h Adrien

#include "OBP60Page.h"
#include "OBP60Data1.h"
#include "OBP60WindRose.h"
#include "OBP60Timer.h"

//forward
class TopMargin;

extern GxGDEW042T2 display;
extern bool heartbeat; 
extern unsigned long timeBefore, timeBefore1, timeAfter;  // for debbuging
extern TopMargin topMargin;

class TopMargin
{
	public: 
	  	TopMargin();
	  	void print(busData *bInfo);
	private:
      	unsigned long usbRxOld;  
		unsigned long usbTxOld;
		unsigned long serRxOld;
		unsigned long serTxOld;
		unsigned long tcpSerRxOld;
		unsigned long tcpSerTxOld;
		unsigned long tcpClRxOld;
		unsigned long tcpClTxOld;
		unsigned long n2kRxOld;
		unsigned long n2kTxOld;

};

void pageUpdate(busData *bInfo);
void buttomStatusLine();
void print1tile(busData *bInfo);   // page with 1 tile
void print2tiles(busData *bInfo);  // page with 2 tiles
void print3tiles(busData *bInfo);  // page with 3 tiles
void print4tiles(busData *bInfo);  // page with 4 tiles

#endif