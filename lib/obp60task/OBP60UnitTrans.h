/*
* Unit transform functions for OBP60 Display
*/
#ifndef UNITTRANS_H
#define UNITTRANS_H
    
#include <Arduino.h>

float mps2kn(float val)
{
	return val*3.6/1.852;
}

float rad2deg(float val)
{ 
    return val*180.0/(3.14159);
}

#endif