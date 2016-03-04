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

#undef min
#undef max

#include <iostream>

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#else
#endif

using namespace std;

ArduinoMockController *ArduinoMockController::mInstance = NULL;

ArduinoMockController::ArduinoMockController() :
        mTimerHandling( REAL_TIMER_HANDLING ),
        mMicroSeconds( 0 ),
        mMilliSeconds( 0 )
{
    initializeTimers();
}

ArduinoMockController::~ArduinoMockController()
{
    mInstance = NULL;
}

ArduinoMockController & ArduinoMockController::getInstance()
{
    if (NULL == mInstance)
    {
        mInstance = new ArduinoMockController();
    }

    return *mInstance;
}

void ArduinoMockController::initializeTimers()
{
    ftime( &mInitialTime );
    gettimeofday( &mInitialTimeVal, NULL );
}


void ArduinoMockController::setPinMode( uint8_t pPinNumber, uint8_t pMode )
{
    if (pPinNumber < 0 || pPinNumber >= MAX_ARDUINO_PINS)
    {
        throw range_error( "Range error: pPinNUmber not in range of allowed pins of the ArduinoMock class." );
    }

    if (pMode != INPUT || pMode != OUTPUT)
    {
        throw range_error( "Range error: pMode is neither INPUT nor OUTPUT." );
    }

    mPinMode[pPinNumber] = pPinMode;
}
