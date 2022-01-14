#ifndef _OBP60WindRose_H
#define _OBP60WindRose_H

#include <Arduino.h>

#include <GxGDEW042T2/GxGDEW042T2.h>    // 4.2" Waveshare S/W 300 x 400 pixel

#include "Ubuntu_Bold8pt7b.h"
#include "Ubuntu_Bold20pt7b.h"
#include "Ubuntu_Bold32pt7b.h"
#include "DSEG7Classic-BoldItalic16pt7b.h"
#include "DSEG7Classic-BoldItalic30pt7b.h"
#include "DSEG7Classic-BoldItalic42pt7b.h"
#include "DSEG7Classic-BoldItalic60pt7b.h"
#include "FreeMonoBold9pt7b.h"
#include "Seven_Segment32pt7b.h"   // need in OBP60Graphics.h Adrien

#include "OBP60Hardware.h"
#include "OBP60Data1.h"

extern float pi;
extern float rWindGraphic; // Radius of circle in pixel for wind graphic	
extern bool heartbeat; 
extern unsigned long timeBefore, timeBefore1, timeAfter;  // for debbuging
extern GxGDEW042T2 display;

void printWindRose(busData *bInfo);  // "Wind Rose" number of tiles 10 graphic page
void drawCenterString(const char *buf, int x, int y);
void drawCentreString(const String &buf, int x, int y);
void printWindCornerInfo(busData *bInfo,int i);
void printWindCircle(busData *bInfo, int angle);
void drawArrow(int angle);
#endif