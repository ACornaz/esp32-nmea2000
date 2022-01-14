#include "OBP60WindRose.h"

void printWindRose(busData *bInfo)  // "Wind Rose" number of tiles 10 graphic page
{   
	static int alpha=0;
  alpha=alpha+2;
  // Apparent Wind Angle diplayed in graphic windrose
  printWindCircle(bInfo, bInfo->AWA.fvalue);

    // debug write time in function
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(200, 80);
    display.print(timeAfter-timeBefore);
}

void drawCenterString(const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x-w/2, y+h/2);
    display.print(buf);
    // display.drawRect(x-w/2,y-h/2,w+1,h+1,0);
}

void drawCentreString(const String &buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void printWindCornerInfo(busData *bInfo,int i)
{
  int k,l;
  dataContainer * dC;
  switch (i)
  {
     case 1:
        k=0;
        l=0;
        dC = &bInfo->TWS;
        break;
      case 2:
        k=1;
        l=0;
        dC = &bInfo->AWS;
        break;
     case 3:
        k=0;
        l=1;
        dC = &bInfo->TWA;
        break;
     case 4:
        k=1;
        l=1;
        dC = &bInfo->AWA;
        break;                      

  };

  display.setFont(&Ubuntu_Bold8pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0+k*320, 20+l*160);
  display.print(dC->title);
  
  // unit
  display.setFont(&Ubuntu_Bold8pt7b);
  display.setCursor(0+k*320, 100+l*160);
  display.print(dC->unit);
 
  // measurements
  display.setFont(&DSEG7Classic_BoldItalic16pt7b);
  display.setCursor(0+k*300, 80+l*160);
  if(dC->valid == true){     // Check vor valid real data
      display.print(dC->svalue);
  }
  else{
      display.print("---");                   // Missing bus data
  }  
}


void printWindCircle(busData *bInfo, int angle)
{
    display.drawCircle(200, 150, rWindGraphic+10,GxEPD_BLACK );
    display.drawCircle(200, 151, rWindGraphic+10,GxEPD_BLACK );
    // display.drawCircle(200, 150, rWindGraphic-10,GxEPD_BLACK );
    display.setFont(&FreeMonoBold9pt7b);
    for(int i=0; i<360; i=i+10)
    {
        float x = 200 + (rWindGraphic-30)*sin(i/180.0*pi);  //  x-coordinate dots
        float y = 150 - (rWindGraphic-30)*cos(i/180.0*pi);  //  y-coordinate cots 
    	  const char *ii;
    	  switch (i)
    	  {
       	  case 0: ii="0"; break;
       	  case 30 : ii="30"; break;
       	  case 60 : ii="60"; break;
          case 90 : ii="90"; break;
          case 120 : ii="120"; break;
          case 150 : ii="150"; break;
          case 180 : ii="180"; break;
          case 210 : ii="210"; break;
          case 240 : ii="240"; break;
          case 270 : ii="270"; break;
          case 300 : ii="300"; break;
          case 330 : ii="330"; break;
          default: break;
        }
    	  if(i % 30 == 0)
        	drawCenterString(ii,(int)x,(int)y);   // angle label
        float x1 = 200 + rWindGraphic*sin(i/180.0*pi);
    	  float y1 = 150 - rWindGraphic*cos(i/180.0*pi);
    	  display.fillCircle((int)x1, (int)y1, 2,GxEPD_BLACK ); 

    	  float sinx=sin(i/180.0*pi);
    	  float cosx=cos(i/180.0*pi); 

        if(i % 30 == 0)
        {
          float dx=2;   // linethickness = 2*dx+1
       	  float xx1 = -dx;
       	  float xx2 = +dx;
       	  float yy1 =  -(rWindGraphic-10);
       	  float yy2 =  -(rWindGraphic+10);
       	  display.fillTriangle(200+(int)(cosx*xx1-sinx*yy1),150+(int)(sinx*xx1+cosx*yy1),
                 200+(int)(cosx*xx2-sinx*yy1),150+(int)(sinx*xx2+cosx*yy1),
                 200+(int)(cosx*xx1-sinx*yy2),150+(int)(sinx*xx1+cosx*yy2),0);
       	  display.fillTriangle(200+(int)(cosx*xx2-sinx*yy1),150+(int)(sinx*xx2+cosx*yy1),
                 200+(int)(cosx*xx1-sinx*yy2),150+(int)(sinx*xx1+cosx*yy2),
                 200+(int)(cosx*xx2-sinx*yy2),150+(int)(sinx*xx2+cosx*yy2),0);  
        }
        drawArrow(angle); 
    }
    printWindCornerInfo(bInfo,1);
    printWindCornerInfo(bInfo,2);
    printWindCornerInfo(bInfo,3);
    printWindCornerInfo(bInfo,4);
}

void drawArrow(int angle)
{
    float sinx=sin(angle/180.0*pi);
    float cosx=cos(angle/180.0*pi);
    // Zeiger als Dreieck mit Basis im Zenrtum 2*breite+1
    float breite=6;
    float xx1 = -breite;
    float xx2 = breite;
    float yy1 = -breite;
    float yy2 = -(rWindGraphic-15);        
    display.fillTriangle(200+(int)(cosx*xx1-sinx*yy1),150+(int)(sinx*xx1+cosx*yy1),
          200+(int)(cosx*xx2-sinx*yy1),150+(int)(sinx*xx2+cosx*yy1),
          200+(int)(cosx*0-sinx*yy2),150+(int)(sinx*0+cosx*yy2),0); 
}

