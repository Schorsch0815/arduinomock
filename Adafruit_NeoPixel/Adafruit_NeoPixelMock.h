/*--------------------------------------------------------------------
  This file based on the Adafruit NeoPixel library.

  NeoPixel is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoPixel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with NeoPixel.  If not, see
  <http://www.gnu.org/licenses/>.

  Modified for mocking
  by Jochen Schales 2016
  --------------------------------------------------------------------*/

#ifndef ADAFRUIT_NEOPIXELMOCK_H
#define ADAFRUIT_NEOPIXELMOCK_H

#include "Arduino.h"
#include <memory.h>

void noInterrupts();

void interrupts();

namespace adafruit
{
#include "/home/jochen/gitRepo/Adafruit_NeoPixel/Adafruit_NeoPixel.h"
};


class Adafruit_NeoPixel : public adafruit::Adafruit_NeoPixel
{

public:
    // Constructor: number of LEDs, pin number, LED type
    Adafruit_NeoPixel( uint16_t pNumberOfLeds, uint8_t pPinNumber = 6, uint8_t pStripType = NEO_GRB + NEO_KHZ800 );
    Adafruit_NeoPixel( void );
    ~Adafruit_NeoPixel();

    void show( void );

    void dump( void );
};

#endif // ADAFRUIT_NEOPIXELMOCK_H
