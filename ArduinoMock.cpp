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

#include <sys/timeb.h>
#include <sys/time.h>
#include <iostream>
#include <stdexcept>

//#include <cstdlib>
//#include <sys/time.h>
//#include <cstdio>

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#else
#endif

using namespace std;

static timeb & initializeTime();
static struct timeval & initializeTimeVal();

static timeb sInitialTime = initializeTime();

static struct timeval sInitialTimeVal = initializeTimeVal();


timeb & initializeTime()
{
    ftime(&sInitialTime);
    return sInitialTime;
}

struct timeval & initializeTimeVal()
{
    gettimeofday(&sInitialTimeVal,NULL);
    return sInitialTimeVal;
}


unsigned long millis()
{
    timeb lCurrent;
    ftime(&lCurrent);
    return (lCurrent.time - sInitialTime.time) * 1000
            + (lCurrent.millitm - sInitialTime.millitm);
}

void delay(unsigned long pMilliseconds)
{
#if defined(WIN32)
    SetLastError(0);
    Sleep(pMilliseconds);
    cerr << "Windows error:" << (GetLastError() ? -1 : 0) << endl;
#elif defined(__linux__)
    usleep(1000 * pMilliseconds);
#else
#error ("no milli sleep available for current platform")
    return;
#endif
}

unsigned long micros()
{
    struct timeval lTimeVal;

    if (gettimeofday(&lTimeVal, NULL))
    {
        throw runtime_error( "Problem calling gettimeofday");
    }

    return (lTimeVal.tv_sec - sInitialTimeVal.tv_sec) * 1000000 + (lTimeVal.tv_usec -sInitialTimeVal.tv_usec);
}

void delayMicroseconds(unsigned long pMicroseconds)
{
#if 0 //defined(WIN32)
    SetLastError(0);
    Sleep(ms);
    cerr << "Windows error:" << (GetLastError() ? -1 : 0) << endl;
#endif
#if defined(__linux__)
    usleep(pMicroseconds);
#else
#error ("no micro sleep available for platform")
    return;
#endif
}


void pinMode(uint8_t, uint8_t)
{

}

void digitalWrite(uint8_t, uint8_t)
{

}

void analogWrite(uint8_t, int)
{

}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return 0;
}

long map(long pValue, long pFromLow, long pFromHigh, long pToLow, long pToHigh)
{
    long lDeltaFrom = pFromHigh - pFromLow;
    long lDeltaTo = pToHigh - pToLow;

    if (pValue < pFromLow || pValue > pFromHigh)
    {
        throw range_error(
                "Range error: pValue is not between pFromLow and pFromHigh.");
    }
    if (0 > lDeltaTo)
    {
        // cerr << "(EE) Range of 'To' values is negative: " << lDeltaTo << endl;
        throw range_error("Range error: ToLow > ToHigh.");
    }
    if (0 > lDeltaFrom)
    {
        // cerr << "(EE) Range of 'From' values is negative: " << lDeltaFrom << endl;
        throw range_error("Range error: FromLow > FromHigh.");
    } else if (0 == lDeltaFrom)
    {
        // cerr << "(EE) division by zero." << endl;
        throw runtime_error("Division by zero.");
    }

    long lResult = (((double) pValue - pFromLow) * lDeltaTo / lDeltaFrom)
            + pToLow;
    return lResult;
}



int digitalRead(uint8_t)
{
    return 0;
}

int analogRead(uint8_t)
{
    return 0;
}

void analogReference(uint8_t mode)
{
}
