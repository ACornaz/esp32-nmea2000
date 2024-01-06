#ifdef BOARD_OBP60S3

#include "Pagedata.h"
#include "OBP60Extensions.h"
#include "movingAvg.h"              // Lib for moving average building

class PageVoltage : public Page
{
bool init = false;                  // Marker for init done
bool keylock = false;               // Keylock
int average = 0;                    // Average type [0...3], 0=off, 1=10s, 2=60s, 3=300s
bool trend = true;                  // Trend indicator [0|1], 0=off, 1=on
double raw = 0;

public:
    PageVoltage(CommonData &common){
        common.logger->logDebug(GwLog::LOG,"Show PageVoltage");
    }
    virtual int handleKey(int key){
         // Change average
        if(key == 1){
            average ++;
            average = average % 4;      // Modulo 4
            return 0;                   // Commit the key
        }

        // Trend indicator
        if(key == 5){
            trend = !trend;
            return 0;                   // Commit the key
        }

        // Code for keylock
        if(key == 11){
            keylock = !keylock;         // Toggle keylock
            return 0;                   // Commit the key
        }
        return key;
    }

    virtual void displayPage(CommonData &commonData, PageData &pageData)
    {
        GwConfigHandler *config = commonData.config;
        GwLog *logger=commonData.logger;
        
        // Get config data
        bool simulation = config->getBool(config->useSimuData);
        String displaycolor = config->getString(config->displaycolor);
        bool holdvalues = config->getBool(config->holdvalues);
        String flashLED = config->getString(config->flashLED);
        String batVoltage = config->getString(config->batteryVoltage);
        String batType = config->getString(config->batteryType);
        String backlightMode = config->getString(config->backlight);

        double value1 = 0;
        double valueTrend = 0;  // Average over 10 values
        
        // Get voltage value
        String name1 = "VBat";

        // Create trend value
        if(init == false){          // Load start values for first page run
            valueTrend = commonData.data.batteryVoltage10;
            init = true;
        }
        else{                       // Reading trend value
            valueTrend = commonData.data.batteryVoltage10;
        }

        // Get raw value for trend indicator
        raw = commonData.data.batteryVoltage;        // Live data

        // Switch average values
        switch (average) {
            case 0:
                value1 = commonData.data.batteryVoltage;        // Live data
                break;
            case 1:
                value1 = commonData.data.batteryVoltage10;      // Average 10s
                break;
            case 2:
                value1 = commonData.data.batteryVoltage60;      // Average 60s
                break;
            case 3:
                value1 = commonData.data.batteryVoltage300;     // Average 300s
                break;
            default:
                value1 = commonData.data.batteryVoltage;        // Default
                break;
        }
        bool valid1 = true;

        // Optical warning by limit violation
        if(String(flashLED) == "Limit Violation"){
            // Limits for Pb battery
            if(String(batType) == "Pb" && (raw < 11.8 || raw > 14.8)){
                setBlinkingLED(true);
                setFlashLED(true);
            }
            if(String(batType) == "Pb" && (raw >= 11.8 && raw <= 14.8)){
                setBlinkingLED(false);
                setFlashLED(false);
            }
            // Limits for Gel battery
            if(String(batType) == "Gel" && (raw < 11.8 || raw > 14.4)){
                setBlinkingLED(true);
            }
            if(String(batType) == "Gel" && (raw >= 11.8 && raw <= 14.4)){
                setBlinkingLED(false);
                setFlashLED(false);
            }
            // Limits for AGM battery
            if(String(batType) == "AGM" && (raw < 11.8 || raw > 14.7)){
                setBlinkingLED(true);
            }
            if(String(batType) == "AGM" && (raw >= 11.8 && raw <= 14.7)){
                setBlinkingLED(false);
                setFlashLED(false);
            }
            // Limits for LiFePo4 battery
            if(String(batType) == "LiFePo4" && (raw < 12.0 || raw > 14.6)){
                setBlinkingLED(true);
            }
            if(String(batType) == "LiFePo4" && (raw >= 12.0 && raw <= 14.6)){
                setBlinkingLED(false);
                setFlashLED(false);
            }
        }
        
        // Logging voltage value
        if (raw == NULL) return;
        LOG_DEBUG(GwLog::LOG,"Drawing at PageVoltage, Type:%s %s:=%f", batType, name1, raw);

        // Draw page
        //***********************************************************

        // Clear display, set background color and text color
        int textcolor = GxEPD_BLACK;
        int pixelcolor = GxEPD_BLACK;
        int bgcolor = GxEPD_WHITE;
        if(displaycolor == "Normal"){
            textcolor = GxEPD_BLACK;
            pixelcolor = GxEPD_BLACK;
            bgcolor = GxEPD_WHITE;
        }
        else{
            textcolor = GxEPD_WHITE;
            pixelcolor = GxEPD_WHITE;
            bgcolor = GxEPD_BLACK;
        }
        //Clear display in obp60task.cpp in main loop

        // Show name
        display.setTextColor(textcolor);
        display.setFont(&Ubuntu_Bold32pt7b);
        display.setCursor(20, 100);
        display.print(name1);                           // Value name

        // Show unit
        display.setTextColor(textcolor);
        display.setFont(&Ubuntu_Bold20pt7b);
        display.setCursor(270, 100);
        display.print("V");

        // Show batery type
        display.setTextColor(textcolor);
        display.setFont(&Ubuntu_Bold8pt7b);
        display.setCursor(295, 100);
        display.print(batType);

        // Show average settings
        display.setTextColor(textcolor);
        display.setFont(&Ubuntu_Bold8pt7b);
        display.setCursor(320, 100);
        switch (average) {
            case 0:
                display.print("Avg: 1s");
                break;
            case 1:
                display.print("Avg: 10s");
                break;
            case 2:
                display.print("Avg: 60s");
                break;
            case 3:
                display.print("Avg: 300s");
                break;
            default:
                display.print("Avg: 1s");
                break;
        } 

        // Reading bus data or using simulation data
        display.setTextColor(textcolor);
        display.setFont(&DSEG7Classic_BoldItalic60pt7b);
        display.setCursor(20, 240);
        if(simulation == true){
            if(batVoltage == "12V"){
                value1 = 12.0;
            }
            if(batVoltage == "24V"){
                value1 = 24.0;
            }
            value1 += float(random(0, 5)) / 10;         // Simulation data
            display.print(value1,1);
        }
        else{
            // Check for valid real data, display also if hold values activated
            if(valid1 == true || holdvalues == true){
                // Resolution switching
                if(value1 < 10){
                    display.print(value1,2);
                }
                if(value1 >= 10 && value1 < 100){
                    display.print(value1,1);
                }
                if(value1 >= 100){
                    display.print(value1,0);
                }
            }
            else{
            display.print("---");                       // Missing bus data
            }  
        }

        // Trend indicator
        // Show trend indicator
        if(trend == true){
            display.fillRect(310, 240, 40, 120, bgcolor);   // Clear area
            display.fillRect(315, 183, 35, 4, textcolor);   // Draw separator
            if(int(raw * 10) > int(valueTrend * 10)){
                displayTrendHigh(320, 174, 11, textcolor);  // Show high indicator
            }
            if(int(raw * 10) < int(valueTrend * 10)){
                displayTrendLow(320, 195, 11, textcolor);   // Show low indicator
            }
        }
        // No trend indicator
        else{
            display.fillRect(310, 240, 40, 120, bgcolor);   // Clear area
        }


        // Key Layout
        display.setTextColor(textcolor);
        display.setFont(&Ubuntu_Bold8pt7b);
        if(keylock == false){
            display.setCursor(10, 290);
            display.print("[AVG]");
            display.setCursor(130, 290);
            display.print("[  <<<<  " + String(commonData.data.actpage) + "/" + String(commonData.data.maxpage) + "  >>>>  ]");
            display.setCursor(293, 290);
                display.print("[TRD]");
            if(String(backlightMode) == "Control by Key"){              // Key for illumination
                display.setCursor(343, 290);
                display.print("[ILUM]");
            }
        }
        else{
            display.setCursor(130, 290);
            display.print(" [    Keylock active    ]");
        }

        // Update display
        display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);    // Partial update (fast)
    };
};

static Page *createPage(CommonData &common){
    return new PageVoltage(common);
}
/**
 * with the code below we make this page known to the PageTask
 * we give it a type (name) that can be selected in the config
 * we define which function is to be called
 * and we provide the number of user parameters we expect (0 here)
 * and will will provide the names of the fixed values we need
 */
PageDescription registerPageVoltage(
    "Voltage",      // Name of page
    createPage,     // Action
    0,              // Number of bus values depends on selection in Web configuration
    {},             // Names of bus values undepends on selection in Web configuration (refer GwBoatData.h)
    true            // Show display header on/off
);

#endif