/*--------------------------------------------------------------------
 * This file is part of the arduinomock library.
 *
 * arduinomock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * arduinomock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RcCarLights.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright: Jochen Schales 2015
 *
 * --------------------------------------------------------------------*/

#include "ArduinoMock.h"
#include "ArduinoMockController.h"

#undef min
#undef max

#include <iostream>

#if defined( WIN32 )
#include <windows.h>
#elif defined( __linux__ )
#include <unistd.h>
#else
#endif

using namespace std;

unsigned long millis()
{
    return ArduinoMockController::getInstance().getMilliSeconds();
}

void delay( unsigned long pMilliseconds )
{
    ArduinoMockController::getInstance().delay( pMilliseconds );
}

unsigned long micros()
{
    return ArduinoMockController::getInstance().getMicroSeconds();
}

void delayMicroseconds( unsigned long pMicroSeconds )
{
    ArduinoMockController::getInstance().delayMicroSeconds( pMicroSeconds );
}

void pinMode( uint8_t pPinNumber, uint8_t pPinMode )
{
    ArduinoMockController::getInstance().setPinMode( pPinNumber, pPinMode );
}

void digitalWrite( uint8_t pPinNumber, uint8_t pValue )
{
    ArduinoMockController::getInstance().setDigitalValue( pPinNumber, pValue );
}

void analogWrite( uint8_t pPinNumber, int pValue )
{
    ArduinoMockController::getInstance().setAnalogValue( pPinNumber, pValue );
}

unsigned long pulseIn( uint8_t pin, uint8_t state, unsigned long timeout )
{
    return ArduinoMockController::getInstance().getPulseValue( pin, state, timeout );
}

unsigned long pulseIn( uint8_t pin, uint8_t state )
{
    return ArduinoMockController::getInstance().getPulseValue( pin, state, 1000 );
}

long map( long pValue, long pFromLow, long pFromHigh, long pToLow, long pToHigh )
{
    long lDeltaFrom = pFromHigh - pFromLow;
    long lDeltaTo = pToHigh - pToLow;

    if ( 0 > lDeltaFrom )
    {
        // cerr << "(EE) Range of 'From' values is negative: " << lDeltaFrom << endl;
        throw range_error( "Range error: FromLow > FromHigh." );
    }
    else if ( 0 == lDeltaFrom )
    {
        // cerr << "(EE) division by zero." << endl;
        throw runtime_error( "Division by zero." );
    }

    if ( pValue < pFromLow || pValue > pFromHigh )
    {
        throw range_error( "Range error: pValue is not between pFromLow and pFromHigh." );
    }

    if ( 0 > lDeltaTo )
    {
        // cerr << "(EE) Range of 'To' values is negative: " << lDeltaTo << endl;
        throw range_error( "Range error: ToLow > ToHigh." );
    }

    long lResult = ( ( (double)pValue - pFromLow ) * lDeltaTo / lDeltaFrom ) + pToLow;
    return lResult;
}

int digitalRead( uint8_t pPinNumber )
{
    return ArduinoMockController::getInstance().getDigitalValue( pPinNumber );
}

int analogRead( uint8_t pPinNUmber )
{
    return ArduinoMockController::getInstance().getAnalogValue( pPinNUmber );
}

/**
 * type for analogReference
 */

void analogReference( uint8_t mode )
{
    ArduinoMockController::getInstance().setAnalogReference( mode );
}

void noInterrupts()
{
}

void interrupts()
{
}
