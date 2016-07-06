/*
 * Adafruit_NeoPixelMock.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: ejocsch
 */

#include <iostream>
#include <iomanip>

#include "Adafruit_NeoPixelMock.h"

using namespace std;

Adafruit_NeoPixel::Adafruit_NeoPixel( uint16_t pNumberOfLeds, uint8_t pPinNumber, uint8_t pStripType )
    : adafruit::Adafruit_NeoPixel( pNumberOfLeds, pPinNumber, pStripType )
{
}

Adafruit_NeoPixel::Adafruit_NeoPixel( void )
{
}

Adafruit_NeoPixel::~Adafruit_NeoPixel()
{
}

void Adafruit_NeoPixel::show( void )
{
    if ( NULL == getPixels() )
    {
        return;
    }

    delay( 50 );
    adafruit::Adafruit_NeoPixel::show();
}

void Adafruit_NeoPixel::dump( void )
{
    for ( uint16_t i = 0; i < numPixels(); ++i )
    {
        uint32_t pixel = getPixelColor( i );

        cout << "Pixel[" << setw( 3 ) << i << "] = Color("      //
             << setw( 3 ) << ( 0xff & ( pixel >> 16 ) ) << ", " //
             << setw( 3 ) << ( 0xff & ( pixel >> 8 ) ) << ", "  //
             << setw( 3 ) << ( 0xff & pixel )                   //
             << ")" << endl;
    }
}
