#include <arduino.h> // is needed for some defintions eg byte ...
#include "OBP60Graphics.h"

TopMargin::TopMargin()
{
  usbRxOld=0;  
  usbTxOld=0;
  serRxOld=0;
  serTxOld=0;
  tcpSerRxOld=0;
  tcpSerTxOld=0;
  tcpClRxOld=0;
  tcpClTxOld=0;
  n2kRxOld=0;
  n2kTxOld=0;
}

void TopMargin::print(busData *bInfo)
{
   if(bInfo->statusline == true){
    // Print status info
    display.setFont(&Ubuntu_Bold8pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(0, 15);
    if(bInfo->wifiApOn){
      display.print(" AP ");
    }
    // If receive new telegram data then display bus name
    if(bInfo->tcpClRx != tcpClRxOld || bInfo->tcpClTx != tcpClTxOld || bInfo->tcpSerRx != tcpSerRxOld || bInfo->tcpSerTx != tcpSerTxOld){
      display.print("TCP ");
    }
    if(bInfo->n2kRx != n2kRxOld || bInfo->n2kTx != n2kTxOld){
      display.print("N2K ");
    }
    if(bInfo->serRx != serRxOld || bInfo->serTx != serTxOld){
      display.print("183 ");
    }
    if(bInfo->usbRx != usbRxOld || bInfo->usbTx != usbTxOld){
      display.print("USB ");
    }
    if(bInfo->gps == true && bInfo->PDOP.valid == true && bInfo->PDOP.fvalue <= 50){
     display.print("GPS");
    }
    // Save old telegram counter
    tcpClRxOld = bInfo->tcpClRx;
    tcpClTxOld = bInfo->tcpClTx;
    tcpSerRxOld = bInfo->tcpSerRx;
    tcpSerTxOld = bInfo->tcpSerTx;
    n2kRxOld = bInfo->n2kRx;
    n2kTxOld = bInfo->n2kTx;
    serRxOld = bInfo->serRx;
    serTxOld = bInfo->serTx;
    usbRxOld = bInfo->usbRx;
    usbTxOld = bInfo->usbTx;

    // Heartbeat as dot
    display.setFont(&Ubuntu_Bold32pt7b);
    display.setCursor(205, 14);
    if(heartbeat == true){
      display.print(".");
    }
    else{
      display.print(" ");
    }
    heartbeat = !heartbeat; 

    // Date and time
    display.setFont(&Ubuntu_Bold8pt7b);
    display.setCursor(230, 15);
    if(bInfo->HDOP.valid == true && bInfo->HDOP.fvalue <= 50){
      char newdate[16] = "";
      if(String(bInfo->dateformat) == "DE"){
        display.print(*bInfo->Date.svalue);
      }
      if(String(*bInfo->dateformat) == "GB"){
        bInfo->Date.svalue[2] = '/';
        bInfo->Date.svalue[5] = '/';
        display.print(*bInfo->Date.svalue);
      }
      if(String(*bInfo->dateformat) == "US"){
        char newdate[16] = "";
        strcpy(newdate, bInfo->Date.svalue);
        newdate[0] = bInfo->Date.svalue[3];
        newdate[1] = bInfo->Date.svalue[4];
        newdate[2] = '/';
        newdate[3] = bInfo->Date.svalue[0];
        newdate[4] = bInfo->Date.svalue[1];
        newdate[5] = '/';
        display.print(newdate);
      }
      display.print(" ");
      if(bInfo->timezone == 0){
        display.print(*bInfo->Time.svalue);
        display.print(" ");
        display.print("UTC");
      }
      else{
        char newtime[16] = "";
        char newhour[3] = "";
        int hour = 0;
        strcpy(newtime, bInfo->Time.svalue);    
        newhour[0] = bInfo->Time.svalue[0];
        newhour[1] = bInfo->Time.svalue[1];
        hour = strtol(newhour, 0, 10);
        if(bInfo->timezone > 0){
          hour += bInfo->timezone;
        }
        else{
          hour += bInfo->timezone + 24;
        }
        hour %= 24;
        sprintf(newhour, "%d", hour);
        newtime[0] = newhour[0];
        newtime[1] = newhour[1];
        display.print(newtime);
        display.print(" ");
        display.print("LOT");
      }
    }
    else{
      display.print("No GPS data");
    }   
  }
}

void pageUpdate(busData *bInfo,bool firstView)
{
    display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  switch (actualPage->numbTiles)
  {
    case 1:
      print1tile(bInfo);
      break;      
    case 2:
      print2tiles(bInfo);
      break;
    case 3:
      print3tiles(bInfo);
      break;
    case 4:
      print4tiles(bInfo);
      break;  
    case 10:
      printWindRose(bInfo);
      break;
    case 11:
      printTimer(bInfo);
      break;
    default:
    ;        
  } 
  // Update display
  if(bInfo->refresh == true){
    if(firstView == true){
      display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);    // Needs partial update before full update to refresh the frame buffer
      display.update(); // Full update
    }
    else{
      display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);    // Partial update (fast)
    }
  }  
  else{
    display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);    // Partial update (fast)
  }
}

void buttomStatusLine()
{
    // Key Layout
  display.setFont(&Ubuntu_Bold8pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(0, 290);
  display.print(" [  <  ]");
  display.setCursor(290, 290);
  display.print("[  >  ]");
  display.setCursor(343, 290);
  display.print("[ILUM]");
}

void print1tile(busData *bInfo)  // page with 1 tile
{
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  for(int i=0;i<actualPage->numbTiles;i++)
  {
    // Title
    display.setFont(&Ubuntu_Bold32pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 100);
    display.print(actualTile->title);

    // unit
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setCursor(270, 100);
    display.print(actualTile->unit);

    // value of measurement
    display.setFont(&DSEG7Classic_BoldItalic60pt7b);
    display.setCursor(20, 240);

    // Reading bus data or using simulation data
    float val = 0;
    if(bInfo->simulation == true)
    {
      val = 54;
      val += float(random(0, 120)) / 10;      // Simulation data
      display.print(val,1);
    }
    else
    {
      if(*actualTile->valid == true){     // Check vor valid real data
        display.print(actualTile->charValue);
      }
      else{
        // display.print("---");                   // Missing bus data
        display.print(actualTile->charValue);   // zeige es doch an debugging
      }  
    }
  }

    // debug write time in function
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(200, 80);
    display.print(timeAfter-timeBefore);
}

void print2tiles(busData *bInfo)  // page with 2 tiles
{
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  display.fillRect(0, 145, 400, 3, GxEPD_BLACK);   // Horizontal line 3 pix
  for(int i=0;i<actualPage->numbTiles;i++)
  {
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(20, 80+i*130);
    display.print(actualTile->title);
  
    // unit
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setCursor(20, 130+i*130);
    display.print(actualTile->unit);
 
    // measurements
    display.setFont(&DSEG7Classic_BoldItalic42pt7b);
    display.setCursor(120, 130+i*130);
   // Reading bus data or using simulation data
    float val = 0;
    if(bInfo->simulation == true){
      val = 54;
      val += float(random(0, 120)) / 10;      // Simulation data
      display.print(val,1);
    }
    else{
      if(*actualTile->valid == true){     // Check vor valid real data
        display.print(actualTile->charValue);
        /*
        val = *actualTile->value;      // Real bus data
        if(val <= 99.9){
          display.print(val,1);
        }
        else{
          display.print(val,0);
        }
        */
      }
      else{
       // display.print("---");                   // Missing bus data
        display.print(actualTile->charValue);   // zeige es doch an debugging
      }  
      
    }
    actualTile = actualTile->next;
  }
}


void print3tiles(busData *bInfo)
{
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  display.fillRect(0, 104, 400, 3, GxEPD_BLACK);   // Horizontal line 3 pix
  display.fillRect(0, 189, 400, 3, GxEPD_BLACK);   // Horizontal line 3 pix
  for(int i=0;i<actualPage->numbTiles;i++)
  {
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(0, 60+i*84);
    display.print(actualTile->title);
  
    // unit
    display.setFont(&Ubuntu_Bold20pt7b);
    display.setCursor(310, 95+i*84);
    display.print(actualTile->unit);
 
    // measurements
    display.setFont(&DSEG7Classic_BoldItalic30pt7b);
    display.setCursor(100, 95+i*84);
    if(*actualTile->valid == true){     // Check vor valid real data
        display.print(actualTile->charValue);
        /*
        val = *actualTile->value;      // Real bus data
        if(val <= 99.9){
          display.print(val,1);
        }
        else{
          display.print(val,0);
        }
        */
      }
      else{
       // display.print("---");                   // Missing bus data
        display.print(actualTile->charValue);   // zeige es doch an debugging
      }  
    actualTile = actualTile->next;
  }
}

void print4tiles(busData *bInfo)
{
  display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);   // Draw white sreen
  topMargin.print(bInfo);
  buttomStatusLine();
  display.fillRect(0, 145, 400, 3, GxEPD_BLACK);   // Horizontal line 3 pix
  display.fillRect(198, 20, 3, 260, GxEPD_BLACK);   // Vertical line 3 pix
  for(int i=0;i<actualPage->numbTiles;i+=2)
  {
    for(int j=0;j<2;j++)
    {
      //title
      display.setFont(&Ubuntu_Bold8pt7b);
      display.setTextColor(GxEPD_BLACK);
      display.setCursor(10+(i/2)*200, 40+j*130);
      display.print(actualTile->title);
  
      // unit
      display.setFont(&Ubuntu_Bold8pt7b);
      display.setCursor(10+(i/2)*200, 130+j*130);
      display.print(actualTile->unit);
 
      // measurements
      display.setFont(&DSEG7Classic_BoldItalic16pt7b);
      display.setCursor(50+(i/2)*200, 95+j*130);
   
      if(*actualTile->valid == true){     // Check vor valid real data
        display.print(actualTile->charValue);
        /*
        val = *actualTile->value;      // Real bus data
        if(val <= 99.9){
          display.print(val,1);
        }
        else{
          display.print(val,0);
        }
        */
      }
      else{
        display.print("---");                   // Missing bus data
        //display.print(actualTile->charValue);   // zeige es doch an debugging
      }  
      actualTile = actualTile->next;
    }
  }
}


