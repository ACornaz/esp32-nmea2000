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
  bool wifiApOn;
  bool wifiClientOn;
  bool wifiClientConnected;
  String wifiApIp;
  String systemName;     // is also AP SSID
  String wifiApPass;
  String wifiClientIp;
  String wifiClientSSID;
  unsigned long usbRx;
  unsigned long usbTx;
  unsigned long serRx;
  unsigned long serTx;
  unsigned long tcpSerRx;
  unsigned long tcpSerTx;
  int tcpClients;
  unsigned long tcpClRx;
  unsigned long tcpClTx;
  bool tcpClientConnected;
  unsigned long n2kRx;
  unsigned long n2kTx; 
  // OBP60 Settings
  char dateformat[3];
  int timezone;
  float draft;
  float fueltank;
  float fuelconsumption;
  float watertank;
  float wastetank;
  float batvoltage;
  char battype[16];
  float batcapacity;
  // OBP60 Hardware
  bool gps;
  bool bme280;
  bool onewire;
  char powermode[16];
  bool simulation;
  // OBP60 Display
  char displaymode[16];
  bool statusline;
  bool refresh;
  char backlight[16];
  char flashled[16];
  // OBP60 Buzzer
  bool buzerror;
  bool buzgps;
  bool buzlimits;
  char buzmode[16];
  int buzpower;
  // OBP60 Pages
  int numpages;
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
} busData;

void initBusInfo(busData *bInfo);
float* valuePtr(busData *bInfo, String pageTile);
char* charPtr(busData *bInfo, String pageTile);
bool* validPtr(busData *bInfo, String pageTile);
dataContainer* dataContPtr(busData *bInfo, String pageTile);

#endif