#ifndef _OBP60Data1_H
#define _OBP60Data1_H

#include <Arduino.h>

typedef struct{
  char title[12];     // name of measurement: AWA etc
  float fvalue;       // float value of measurement
  char svalue[16];    // char value
  char unit[8];       // char Unit
  bool valid;         // valid flag for new value
  bool primary;       // primary = true, Data in GwApi::BoatValue, 
                      // primary = false, Data must be calculated with other values
  bool longValue;     // longValue=true: 24° 20.500' N    130° 04.333' E  max 14 characters
                      // longValue=false 2.3 m or 17.4 kn 187 deg  max 4 characters 
} dataContainer;

typedef struct{
  // Gateway status infos
  bool wifiApOn;                    // Status access point [on|off]
  bool wifiClientConnected;         // Client connected [yes|no]
  unsigned long usbRx;                  // USB receive traffic
  unsigned long usbTx;                  // USB send traffic
  unsigned long serRx;                  // MNEA0183 serial receive traffic
  unsigned long serTx;                  // NMEA0183 serial send traffic
  unsigned long tcpSerRx;               // MNEA0183 TCP server receive traffic
  unsigned long tcpSerTx;               // MNEA0183 TCP server send traffic
  int tcpClients;                       // Number of connected TCP clients
  unsigned long tcpClRx;                // MNEA0183 TCP client receive traffic
  unsigned long tcpClTx;                // MNEA0183 TCP client send traffic
  bool tcpClientConnected;          // Connected TCP clients
  unsigned long n2kRx;                  // NMEA2000 CAN receive traffic
  unsigned long n2kTx;                  // NMEA2000 CAN send traffic
  // System Settings
  char systemname[32];                 // System name show on web page and mDNS name
  char wifissid[32];                   // WiFi access point SSID
  char wifipass[32];                   // WiFi access point password
  bool useadminpass;                // Use admin password [on|off]
  char adminpassword[32];              // Admin password
  char loglevel[16];                   // Loglevel [off|error|log|debug]
  // WiFi client settings
  bool wificlienton;                // Is WiFi client on [on|off]
  char wificlientssid[32];             // Wifi client SSID
  char wificlientpass[32];             // Wifi client password
  // OBP60 Settings
  char lengthformat[16];               // Length format [m|ft]
  char distanceformat[16];             // Distance format [m|km|nm]
  char speedformat[16];                // Speed format [m/s|km/h|kn]
  char windspeedformat[16];            // Speed format [m/s|km/h|kn|bft]
  char tempformat[16];                 // Temperature format [K|C|F]
  char dateformat[3];                  // Date format for status line [DE|GB|US]
  int timezone;                         // Time zone [-12...+12]
  float draft;                          // Boat draft up to keel [m]
  float fueltank;                       // Fuel tank capacity [0...10m]
  float fuelconsumption;                // Fuel consumption [0...1000l/min]
  float watertank;                      // Water tank kapacity [0...5000l]
  float wastetank;                      // Waste tank kapacity [0...5000l]
  float batvoltage;                     // Battery voltage [0...1000V]
  char battype[16];                    // Battery type [Pb|Gel|AGM|LiFePo4]
  float batcapacity;                    // Battery capacity [0...10000Ah]
  // OBP60 Hardware
  bool gps;                         // Internal GPS [on|off]
  bool bme280;                      // Internat BME280 [on|off]
  bool onewire;                     // Internal 1Wire bus [on|off]
  char powermode[16];                  // Power mode [Max Power|Only 3.3V|Only 5.0V|Min Power]
  bool simulation;                  // Simulation data [on|off]
  // OBP60 Display
  char displaymode[16];                // Dislpay mode [White Screen|Logo|Logo + QR Code|Off]
  bool statusline;                   // Show status line [on|off]
  bool refresh;                     // Refresh display after select a new page [on|off]
  bool holdvalues;                  // Hold values on missing data stream [on|off]
  char backlight[16];                  // Backlight mode [Off|Control by Sun|Control by Bus|Control by Time|Control by Key|On]
  char flashled[16];                   // Flash LED mode [Off|Bus Data|GPX Fix|Limits Overrun]
  // OBP60 Buzzer
  bool buzerror;                    // Buzzer error [on|off]
  bool buzgps;                      // Buzzer by GPS error [on|off]
  bool buzlimits;                   // Buzzer by limit underruns and overruns [on|off]
  char buzmode[16];                    // Buzzer mode [Off|Short Single Beep|Lond Single Beep|Beep until Confirmation]
  int buzpower;                         // Buzzer power [0...100%]
  // OBP60 Pages
  int numpages;                         // Numper of listed pages
  // Bus data   defined measurements: see GwBoatData.h
  dataContainer AWA;
  dataContainer AWD;
  dataContainer AWS;
  dataContainer Altitude;
  dataContainer BTW;
  dataContainer COG;
  dataContainer DTW;
  dataContainer Date;
  dataContainer DepthTransducer;
  dataContainer Deviation;
  dataContainer GPSDate;
  dataContainer GPSTime;
  dataContainer HDOP;
  dataContainer Heading;
  dataContainer Latitude;
  dataContainer Log;
  dataContainer Longitude;
  dataContainer MagneticHeading;
  dataContainer MaxAWS;
  dataContainer MaxTWS;
  dataContainer MaxSTW;
  dataContainer PDOP;
  dataContainer ROT;
  dataContainer RudderPosition;
  dataContainer SOG;
  dataContainer STW;
  dataContainer SatInfo;
  dataContainer Time;
  dataContainer TWA;
  dataContainer TWD;
  dataContainer TWS;
  dataContainer Timezone;
  dataContainer TripLog;
  dataContainer VDOP;
  dataContainer Variation;
  dataContainer WPLatitude;
  dataContainer WPLongitude;
  dataContainer WaterDepth;
  dataContainer WaterTemperature;
  dataContainer XTE;
  float TWDarray[300][2];
} busData;

void initBusInfo(busData *bInfo);
float* valuePtr(busData *bInfo, String pageTile);
char* charPtr(busData *bInfo, String pageTile);
bool* validPtr(busData *bInfo, String pageTile);
dataContainer* dataContPtr(busData *bInfo, String pageTile);
void printSvalue(dataContainer * dc);
void storeTWD(busData *bInfo);

#endif