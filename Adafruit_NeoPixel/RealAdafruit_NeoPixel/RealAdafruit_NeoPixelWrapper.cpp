/*
 * RealAdafruit_NeoPixelWrapper.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ejocsch
 */

#include "Arduino.h"
#include <memory.h>
void noInterrupts()
{
}

void interrupts()
{
}

namespace adafruit
{
#include "./Adafruit_NeoPixel.h"

#include "./Adafruit_NeoPixel.cpp"
};

