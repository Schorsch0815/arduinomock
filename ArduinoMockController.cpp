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

#include "ArduinoMockController.h"

#include <iostream>
#include <stdexcept>

#include "Arduino.h"

#if defined( WIN32 )
#include <windows.h>
#elif defined( __linux__ )
#include <unistd.h>
#else
#endif

using namespace std;

ArduinoMockController ArduinoMockController::sInstance;

ArduinoMockController::ArduinoMockController()
    : mTimerMode( ArduinoMockController::REALTIME_TIMER_MODE )
    , mMicroSeconds( 0 )
    , mMilliSeconds( 0 )
    , mPinSimulationMode( MANUAL_PIN_MODE )
    , mAnalogReferenceMode( DEFAULT )
{
    reset();
}

ArduinoMockController::~ArduinoMockController() {}

void ArduinoMockController::reset()
{
    mTimerMode = ArduinoMockController::REALTIME_TIMER_MODE;
    initTimeHandling();

    mPinSimulationMode = MANUAL_PIN_MODE;
    mAnalogReferenceMode = DEFAULT;

    for ( int i = 0; i < MAX_ARDUINO_PINS; ++i )
    {
        mPinMode[i] = INPUT;
        mPinValues[i] = 0;
    }
}

ArduinoMockController &ArduinoMockController::getInstance() { return sInstance; }

void ArduinoMockController::initTimeHandling()
{
    mMicroSeconds = 0;
    mMilliSeconds = 0;

    if ( REALTIME_TIMER_MODE == getTimerMode() )
    {
        ftime( &mInitialTime );
        gettimeofday( &mInitialTimeVal, NULL );
    }
    else
    {
        mInitialTime.time = 0;
        mInitialTime.millitm = 0;
        mInitialTime.timezone = 0;
        mInitialTime.dstflag = 0;

        mInitialTimeVal.tv_sec = 0;
        mInitialTimeVal.tv_usec = 0;
    }
}

void ArduinoMockController::setPinMode( uint8_t pPinNumber, uint8_t pMode )
{
    if ( pPinNumber < 0 || pPinNumber >= MAX_ARDUINO_PINS )
    {
        throw range_error( "Range error: pPinNumber not in range of allowed pins of the ArduinoMock class." );
    }

    if ( pMode != INPUT && pMode != OUTPUT )
    {
        std::cout << "pMode = " << (int)pMode << endl;
        throw range_error( "Range error: pMode is neither INPUT nor OUTPUT." );
    }

    mPinMode[pPinNumber] = pMode;
}

unsigned long ArduinoMockController::getMicroSeconds() const
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
        struct timeval lTimeVal;

        if ( gettimeofday( &lTimeVal, NULL ) )
        {
            throw std::runtime_error( "Problem calling gettimeofday" );
        }

        return ( lTimeVal.tv_sec - mInitialTimeVal.tv_sec ) * 1000000 + ( lTimeVal.tv_usec - mInitialTimeVal.tv_usec );
    }
    return mMicroSeconds;
}

void ArduinoMockController::setMicroSeconds( unsigned long pMicroSeconds )
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
        throw logic_error( "Cannot change micro seconds when using real time timer mode!" );
    }
    else
    {
        mMicroSeconds = pMicroSeconds;
        mMilliSeconds = pMicroSeconds / 1000;
    }
}

unsigned long ArduinoMockController::getMilliSeconds() const
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
        timeb lCurrent;
        ftime( &lCurrent );
        return ( lCurrent.time - mInitialTime.time ) * 1000 + ( lCurrent.millitm - mInitialTime.millitm );
    }
    return mMilliSeconds;
}

void ArduinoMockController::setMilliSeconds( unsigned long pMilliSeconds )
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
        throw logic_error( "Cannot change milli seconds when using real time timer mode!" );
    }
    else
    {
        mMilliSeconds = pMilliSeconds;
        mMicroSeconds = pMilliSeconds * 1000;
    }
}

void ArduinoMockController::delay( unsigned long pMilliSeconds )
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
#if defined( WIN32 )
        SetLastError( 0 );
        Sleep( pMilliSeconds );
        cerr << "Windows error:" << ( GetLastError() ? -1 : 0 ) << endl;
#elif defined( __linux__ )
        usleep( 1000 * pMilliSeconds );
#else
#error("no milli sleep available for current platform")
        return;
#endif
    }
    else
    {
        setMilliSeconds( getMilliSeconds() + pMilliSeconds );
    }
}

void ArduinoMockController::delayMicroSeconds( unsigned long pMicroSeconds )
{
    if ( ArduinoMockController::REALTIME_TIMER_MODE == getTimerMode() )
    {
#if 0 // defined(WIN32)
        SetLastError(0);
        Sleep(ms);
        cerr << "Windows error:" << (GetLastError() ? -1 : 0) << endl;
#endif
#if defined( __linux__ )
        usleep( pMicroSeconds );
#else
#error("no micro sleep available for platform")
        return;
#endif
    }
    else
    {
        setMicroSeconds( getMicroSeconds() + pMicroSeconds );
    }
}

uint8_t ArduinoMockController::getPinMode( uint8_t pPinNumber )
{
    if ( 0 > pPinNumber || MAX_ARDUINO_PINS <= pPinNumber )
    {
        throw std::range_error( "Pin number is out of range." );
    }

    return mPinMode[pPinNumber];
}

void ArduinoMockController::setPinValue( uint8_t pPinNumber, int pValue )
{
    if ( 0 > pPinNumber || MAX_ARDUINO_PINS <= pPinNumber )
    {
        throw std::range_error( "Pin number is out of range." );
    }

    mPinValues[pPinNumber] = pValue;
}

int ArduinoMockController::getPinValue( uint8_t pPinNumber )
{
    if ( 0 > pPinNumber || MAX_ARDUINO_PINS <= pPinNumber )
    {
        throw std::range_error( "Pin number is out of range." );
    }

    return mPinValues[pPinNumber];
}

void ArduinoMockController::setAnalogReference( uint8_t pAnalogReferenceMode )
{
    if ( 0 > pAnalogReferenceMode || 4 <= pAnalogReferenceMode )
    {
        throw std::range_error( "analog reference mode is out of range." );
    }

    mAnalogReferenceMode = pAnalogReferenceMode;
}
