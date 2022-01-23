#ifndef _OBP60Timer_H
#define _OBP60Timer_H

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
#include "OBP60Graphics.h"
#include "OBP60Data1.h"

extern unsigned long timeBefore, timeBefore1, timeAfter;  // for debbuging
extern GxGDEW042T2 display;

void printTimer(busData *bInfo, String *kAction);  // Start Timer
#endif