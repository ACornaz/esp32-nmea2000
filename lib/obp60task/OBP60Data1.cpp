#include <Arduino.h>
#include "OBP60Data1.h"

void initBusInfo(busData *bInfo)
{
    // Gateway status infos
  bInfo->wifiApOn = false;                    // Status access point [on|off]
  bInfo->wifiClientConnected = false;         // Client connected [yes|no]
  bInfo->usbRx = 0;                  // USB receive traffic
  bInfo->usbTx = 0;                  // USB send traffic
  bInfo->serRx = 0;                  // MNEA0183 serial receive traffic
  bInfo->serTx = 0;                  // NMEA0183 serial send traffic
  bInfo->tcpSerRx = 0;               // MNEA0183 TCP server receive traffic
  bInfo->tcpSerTx = 0;               // MNEA0183 TCP server send traffic
  bInfo->tcpClients = 0;                       // Number of connected TCP clients
  bInfo->tcpClRx = 0;                // MNEA0183 TCP client receive traffic
  bInfo->tcpClTx = 0;                // MNEA0183 TCP client send traffic
  bInfo->tcpClientConnected = false;          // Connected TCP clients
  bInfo->n2kRx = 0;                  // NMEA2000 CAN receive traffic
  bInfo->n2kTx = 0;                  // NMEA2000 CAN send traffic
  // System Settings
  strcpy(bInfo->systemname,"");                 // System name show on web page and mDNS name
  strcpy(bInfo->wifissid, "");                   // WiFi access point SSID
  strcpy(bInfo->wifipass, "");                   // WiFi access point password
  bInfo->useadminpass = false;                // Use admin password [on|off]
  strcpy(bInfo->adminpassword, "");              // Admin password
  strcpy(bInfo->loglevel, "");                   // Loglevel [off|error|log|debug]
  // WiFi client settings
  bInfo->wificlienton = false;                // Is WiFi client on [on|off]
  strcpy(bInfo->wificlientssid, "");             // Wifi client SSID
  strcpy(bInfo->wificlientpass, "");             // Wifi client password
  // OBP60 Settings
  strcpy(bInfo->lengthformat, "");               // Length format [m|ft]
  strcpy(bInfo->distanceformat, "");             // Distance format [m|km|nm]
  strcpy(bInfo->speedformat, "");                // Speed format [m/s|km/h|kn]
  strcpy(bInfo->windspeedformat, "");            // Speed format [m/s|km/h|kn|bft]
  strcpy(bInfo->tempformat, "");                 // Temperature format [K|C|F]
  strcpy(bInfo->dateformat, "");                  // Date format for status line [DE|GB|US]
  bInfo->timezone = 0;                         // Time zone [-12...+12]
  bInfo->draft = 0;                          // Boat draft up to keel [m]
  bInfo->fueltank = 0;                       // Fuel tank capacity [0...10m]
  bInfo->fuelconsumption = 0;                // Fuel consumption [0...1000l/min]
  bInfo->watertank = 0;                      // Water tank kapacity [0...5000l]
  bInfo->wastetank = 0;                      // Waste tank kapacity [0...5000l]
  bInfo->batvoltage = 0;                     // Battery voltage [0...1000V]
  strcpy(bInfo->battype, "");                    // Battery type [Pb|Gel|AGM|LiFePo4]
  bInfo->batcapacity = 0;                    // Battery capacity [0...10000Ah]
  // OBP60 Hardware
  bInfo->gps = false;                         // Internal GPS [on|off]
  bInfo->bme280 = false;                      // Internat BME280 [on|off]
  bInfo->onewire = false;                     // Internal 1Wire bus [on|off]
  strcpy(bInfo->powermode, "");                  // Power mode [Max Power|Only 3.3V|Only 5.0V|Min Power]
  bInfo->simulation = false;                  // Simulation data [on|off]
  // OBP60 Display
  strcpy(bInfo->displaymode, "");                // Dislpay mode [White Screen|Logo|Logo + QR Code|Off]
  bInfo->statusline = true;                   // Show status line [on|off]
  bInfo->refresh = false;                     // Refresh display after select a new page [on|off]
  bInfo->holdvalues = false;                  // Hold values on missing data stream [on|off]
  strcpy(bInfo->backlight, "");                  // Backlight mode [Off|Control by Sun|Control by Bus|Control by Time|Control by Key|On]
  strcpy(bInfo->flashled, "");                   // Flash LED mode [Off|Bus Data|GPX Fix|Limits Overrun]
  // OBP60 Buzzer
  bInfo->buzerror = false;                    // Buzzer error [on|off]
  bInfo->buzgps = false;                      // Buzzer by GPS error [on|off]
  bInfo->buzlimits = false;                   // Buzzer by limit underruns and overruns [on|off]
  strcpy(bInfo->buzmode, "");                    // Buzzer mode [Off|Short Single Beep|Lond Single Beep|Beep until Confirmation]
  bInfo->buzpower = 0;                         // Buzzer power [0...100%]
  // OBP60 Pages
  bInfo->numpages = 1;                         // Numper of listed pages
  // title
  strcpy(bInfo->AWA.title,"AWA");
  strcpy(bInfo->AWD.title,"AWD");
  strcpy(bInfo->AWS.title,"AWS");
  strcpy(bInfo->Altitude.title,"Altitude");
  strcpy(bInfo->BTW.title,"BTW");
  strcpy(bInfo->COG.title,"COG");
  strcpy(bInfo->DTW.title,"DTW");
  strcpy(bInfo->Date.title,"Date");
  strcpy(bInfo->DepthTransducer.title,"DepthTrans");
  strcpy(bInfo->Deviation.title,"Deviation");
  strcpy(bInfo->HDOP.title,"HDOP");
  strcpy(bInfo->Heading.title,"Heading");
  strcpy(bInfo->Latitude.title,"Latitude");
  strcpy(bInfo->Log.title,"Log");
  strcpy(bInfo->Longitude.title,"Longitude");
  strcpy(bInfo->MagneticHeading.title,"MagnHeading");
  strcpy(bInfo->MaxAWS.title,"MaxAWS");
  strcpy(bInfo->MaxTWS.title,"MaxTWS");
  strcpy(bInfo->PDOP.title,"PDOP");
  strcpy(bInfo->ROT.title,"ROT");
  strcpy(bInfo->RudderPosition.title,"RudderPos");
  strcpy(bInfo->SOG.title,"SOG");
  strcpy(bInfo->STW.title,"STW");
  strcpy(bInfo->SatInfo.title,"SatInfo");
  strcpy(bInfo->Time.title,"Time");
  strcpy(bInfo->TWA.title,"TWA");
  strcpy(bInfo->TWD.title,"TWD");
  strcpy(bInfo->TWS.title,"TWS");
  strcpy(bInfo->Timezone.title,"TimeZone");
  strcpy(bInfo->TripLog.title,"TripLog");
  strcpy(bInfo->VDOP.title,"VDOP");
  strcpy(bInfo->Variation.title,"Variation");
  strcpy(bInfo->WPLatitude.title,"WPLatitude");
  strcpy(bInfo->WPLongitude.title,"WPLongitude");
  strcpy(bInfo->WaterDepth.title,"WaterDepth");
  strcpy(bInfo->WaterTemperature.title,"WaterTemp");
  strcpy(bInfo->XTE.title,"XTE");


  strcpy(bInfo->AWA.unit,"deg");
  strcpy(bInfo->AWD.unit,"deg");
  strcpy(bInfo->AWS.unit,"kn");
  strcpy(bInfo->Altitude.unit,"m");
  strcpy(bInfo->BTW.unit,"deg");
  strcpy(bInfo->COG.unit,"deg");
  strcpy(bInfo->DTW.unit,"nm");
  strcpy(bInfo->Date.unit,"");
  strcpy(bInfo->DepthTransducer.unit,"m");
  strcpy(bInfo->Deviation.unit,"deg");
  strcpy(bInfo->HDOP.unit,"");
  strcpy(bInfo->Heading.unit,"deg");
  strcpy(bInfo->Latitude.unit,"");
  strcpy(bInfo->Log.unit,"nm");
  strcpy(bInfo->Longitude.unit,"");
  strcpy(bInfo->MagneticHeading.unit,"deg");
  strcpy(bInfo->MaxAWS.unit,"deg");
  strcpy(bInfo->MaxTWS.unit,"kn");
  strcpy(bInfo->PDOP.unit,"nm");
  strcpy(bInfo->ROT.unit,"deg/min");
  strcpy(bInfo->RudderPosition.unit,"deg");
  strcpy(bInfo->SOG.unit,"kn");
  strcpy(bInfo->STW.unit,"kn");
  strcpy(bInfo->SatInfo.unit,"");
  strcpy(bInfo->Time.unit,"");
  strcpy(bInfo->TWA.unit,"deg");
  strcpy(bInfo->TWD.unit,"deg");
  strcpy(bInfo->TWS.unit,"kn");
  strcpy(bInfo->Timezone.unit,"h");
  strcpy(bInfo->TripLog.unit,"nm");
  strcpy(bInfo->VDOP.unit,"");
  strcpy(bInfo->Variation.unit,"deg");
  strcpy(bInfo->WPLatitude.unit,"");
  strcpy(bInfo->WPLongitude.unit,"");
  strcpy(bInfo->WaterDepth.unit,"m");
  strcpy(bInfo->WaterTemperature.unit,"C");
  strcpy(bInfo->XTE.unit,"nm");

// longValue
  bInfo->AWA.longValue=false;
  bInfo->AWD.longValue=false;
  bInfo->AWS.longValue=false;
  bInfo->Altitude.longValue=false;
  bInfo->BTW.longValue=false;
  bInfo->COG.longValue=false;
  bInfo->DTW.longValue=false;
  bInfo->Date.longValue=true;
  bInfo->DepthTransducer.longValue=false;
  bInfo->Deviation.longValue=false;
  bInfo->HDOP.longValue=false;
  bInfo->Heading.longValue=false;
  bInfo->Latitude.longValue=true;
  bInfo->Log.longValue=false;
  bInfo->Longitude.longValue=true;
  bInfo->MagneticHeading.longValue=false;
  bInfo->MaxAWS.longValue=false;
  bInfo->MaxTWS.longValue=false;
  bInfo->PDOP.longValue=false;
  bInfo->ROT.longValue=false;
  bInfo->RudderPosition.longValue=false;
  bInfo->SOG.longValue=false;
  bInfo->STW.longValue=false;
  bInfo->SatInfo.longValue=false;
  bInfo->Time.longValue=true;
  bInfo->TWA.longValue=false;
  bInfo->TWD.longValue=false;
  bInfo->TWS.longValue=false;
  bInfo->Timezone.longValue=false;
  bInfo->TripLog.longValue=false;
  bInfo->VDOP.longValue=false;
  bInfo->Variation.longValue=false;
  bInfo->WPLatitude.longValue=false;
  bInfo->WPLongitude.longValue=false;
  bInfo->WaterDepth.longValue=false;
  bInfo->WaterTemperature.longValue=false;
  bInfo->XTE.longValue=false;
}

float* valuePtr(busData *bInfo, String pageTile)
{
  float v=bInfo->SOG.fvalue;
     return(&bInfo->SOG.fvalue);
}

// return a pointer to the string value (svalue) of the measurement 
// to be displayed on the display via a page 
char* charPtr(busData *bInfo, String pageTile)
{  
  if(pageTile == "Off")     return bInfo->SOG.svalue;  // not correct!!! to be corrected
  if(pageTile == "GPSDate") return bInfo->GPSDate.svalue;
  if(pageTile == "GPSTime") return bInfo->GPSTime.svalue;
  if(pageTile == "HDOP")    return bInfo->HDOP.svalue;
  if(pageTile == "Latitude")  return bInfo->Latitude.svalue;
  if(pageTile == "Longitude") return bInfo->Longitude.svalue;
  if(pageTile == "PDOP")    return bInfo->PDOP.svalue;
  if(pageTile == "SatInfo") return bInfo->SatInfo.svalue;
  if(pageTile == "VPOD")    return bInfo->VDOP.svalue;
  if(pageTile == "WPLatitude") return bInfo->WPLatitude.svalue;
  if(pageTile == "WPLongitude") return bInfo->WPLongitude.svalue;
  if(pageTile == "AWA")     return bInfo->AWA.svalue;
  if(pageTile == "COG")     return bInfo->COG.svalue;
  if(pageTile == "AWD")     return bInfo->AWD.svalue;
  if(pageTile == "BTW")     return bInfo->BTW.svalue;
  if(pageTile == "Deviation") return bInfo->Deviation.svalue;
  if(pageTile == "Haeding") return bInfo->Heading.svalue;
  if(pageTile == "RudderAngleIndicator") return bInfo->RudderPosition.svalue;
  if(pageTile == "TWA")     return bInfo->TWA.svalue;
  if(pageTile == "TWD")     return bInfo->TWD.svalue;
  if(pageTile == "Variation") return bInfo->Variation.svalue;
  if(pageTile == "AWS")     return bInfo->AWS.svalue;
  if(pageTile == "MaxAWS")  return bInfo->MaxAWS.svalue;
  if(pageTile == "MaxTWS")  return bInfo->MaxTWS.svalue;
  if(pageTile == "TWS")     return bInfo->TWS.svalue;
  if(pageTile == "STW")     return bInfo->STW.svalue;
  if(pageTile == "MaxSTW")  return bInfo->MaxSTW.svalue;
  if(pageTile == "SOG")     return bInfo->SOG.svalue;
  if(pageTile == "TWS")     return bInfo->TWS.svalue;
  if(pageTile == "Depth")   return bInfo->DepthTransducer.svalue;
  if(pageTile == "WaterDepth") return bInfo->WaterDepth.svalue;
  if(pageTile == "DTW")     return bInfo->DTW.svalue;
  if(pageTile == "Log")     return bInfo->Log.svalue;
  if(pageTile == "TripLog") return bInfo->TripLog.svalue;
  if(pageTile == "XTE")     return bInfo->XTE.svalue;      
  if(pageTile == "ROT")     return bInfo->ROT.svalue;
  if(pageTile == "Timezone") return bInfo->Timezone.svalue;
  if(pageTile == "WaterTemp") return bInfo->WaterDepth.svalue;

  return bInfo->AWA.svalue;  // default: to be corrected
}

bool* validPtr(busData *bInfo, String pageTile)
{ 
  if(pageTile == "Off")     return &bInfo->SOG.valid;  // not correct!!! to be corrected
  if(pageTile == "GPSDate") return &bInfo->GPSDate.valid;
  if(pageTile == "GPSTime") return &bInfo->GPSTime.valid;
  if(pageTile == "HDOP")    return &bInfo->HDOP.valid;
  if(pageTile == "Latitude")  return &bInfo->Latitude.valid;
  if(pageTile == "Longitude") return &bInfo->Longitude.valid;
  if(pageTile == "PDOP")    return &bInfo->PDOP.valid;
  if(pageTile == "SatInfo") return &bInfo->SatInfo.valid;
  if(pageTile == "VPOD")    return &bInfo->VDOP.valid;
  if(pageTile == "WPLatitude") return &bInfo->WPLatitude.valid;
  if(pageTile == "WPLongitude") return &bInfo->WPLongitude.valid;
  if(pageTile == "AWA")     return &bInfo->AWA.valid;
  if(pageTile == "COG")     return &bInfo->COG.valid;
  if(pageTile == "AWD")     return &bInfo->AWD.valid;
  if(pageTile == "BTW")     return &bInfo->BTW.valid;
  if(pageTile == "Deviation") return &bInfo->Deviation.valid;
  if(pageTile == "Haeding") return &bInfo->Heading.valid;
  if(pageTile == "RudderAngleIndicator") return &bInfo->RudderPosition.valid;
  if(pageTile == "TWA")     return &bInfo->TWA.valid;
  if(pageTile == "TWD")     return &bInfo->TWD.valid;
  if(pageTile == "Variation") return &bInfo->Variation.valid;
  if(pageTile == "AWS")     return &bInfo->AWS.valid;
  if(pageTile == "MaxAWS")  return &bInfo->MaxAWS.valid;
  if(pageTile == "MaxTWS")  return &bInfo->MaxTWS.valid;
  if(pageTile == "TWS")     return &bInfo->TWS.valid;
  if(pageTile == "STW")     return &bInfo->STW.valid;
  if(pageTile == "MaxSTW")  return &bInfo->MaxSTW.valid;
  if(pageTile == "SOG")     return &bInfo->SOG.valid;
  if(pageTile == "TWS")     return &bInfo->TWS.valid;
  if(pageTile == "Depth")   return &bInfo->DepthTransducer.valid;
  if(pageTile == "WaterDepth") return &bInfo->WaterDepth.valid;
  if(pageTile == "DTW")     return &bInfo->DTW.valid;
  if(pageTile == "Log")     return &bInfo->Log.valid;
  if(pageTile == "TripLog") return &bInfo->TripLog.valid;
  if(pageTile == "XTE")     return &bInfo->XTE.valid;      
  if(pageTile == "ROT")     return &bInfo->ROT.valid;
  if(pageTile == "Timezone") return &bInfo->Timezone.valid;
  if(pageTile == "WaterTemp") return &bInfo->WaterDepth.valid;

  return &bInfo->AWA.valid;  // default to be corrected
}

dataContainer* dataContPtr(busData *bInfo, String pageTile)
{ 
  if(pageTile == "Off")     return &bInfo->SOG;  // not correct!!! to be corrected
  if(pageTile == "GPSDate") return &bInfo->GPSDate;
  if(pageTile == "GPSTime") return &bInfo->GPSTime;
  if(pageTile == "HDOP")    return &bInfo->HDOP;
  if(pageTile == "Latitude")  return &bInfo->Latitude;
  if(pageTile == "Longitude") return &bInfo->Longitude;
  if(pageTile == "PDOP")    return &bInfo->PDOP;
  if(pageTile == "SatInfo") return &bInfo->SatInfo;
  if(pageTile == "VPOD")    return &bInfo->VDOP;
  if(pageTile == "WPLatitude") return &bInfo->WPLatitude;
  if(pageTile == "WPLongitude") return &bInfo->WPLongitude;
  if(pageTile == "AWA")     return &bInfo->AWA;
  if(pageTile == "COG")     return &bInfo->COG;
  if(pageTile == "AWD")     return &bInfo->AWD;
  if(pageTile == "BTW")     return &bInfo->BTW;
  if(pageTile == "Deviation") return &bInfo->Deviation;
  if(pageTile == "Haeding") return &bInfo->Heading;
  if(pageTile == "RudderAngleIndicator") return &bInfo->RudderPosition;
  if(pageTile == "TWA")     return &bInfo->TWA;
  if(pageTile == "TWD")     return &bInfo->TWD;
  if(pageTile == "Variation") return &bInfo->Variation;
  if(pageTile == "AWS")     return &bInfo->AWS;
  if(pageTile == "MaxAWS")  return &bInfo->MaxAWS;
  if(pageTile == "MaxTWS")  return &bInfo->MaxTWS;
  if(pageTile == "TWS")     return &bInfo->TWS;
  if(pageTile == "STW")     return &bInfo->STW;
  if(pageTile == "MaxSTW")  return &bInfo->MaxSTW;
  if(pageTile == "SOG")     return &bInfo->SOG;
  if(pageTile == "TWS")     return &bInfo->TWS;
  if(pageTile == "Depth")   return &bInfo->DepthTransducer;
  if(pageTile == "WaterDepth") return &bInfo->WaterDepth;
  if(pageTile == "DTW")     return &bInfo->DTW;
  if(pageTile == "Log")     return &bInfo->Log;
  if(pageTile == "TripLog") return &bInfo->TripLog;
  if(pageTile == "XTE")     return &bInfo->XTE;      
  if(pageTile == "ROT")     return &bInfo->ROT;
  if(pageTile == "Timezone") return &bInfo->Timezone;
  if(pageTile == "WaterTemp") return &bInfo->WaterDepth;

  return  &bInfo->AWA;
}

void printSvalue(dataContainer * dc)
{
  if(dc->fvalue<0.0)
  {
    if(dc->fvalue<10)
      sprintf(dc->svalue , "  %4.0f", dc->fvalue);
  }
  
}