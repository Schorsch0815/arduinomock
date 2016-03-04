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

#ifndef ARDUINO_MOCK_CONTROLLER_H
#define ARDUINO_MOCK_CONTROLLER_H

#include <stdint.h>
#include <stdexcept>
#include <sys/timeb.h>
#include <sys/time.h>

class ArduinoMockController
{
    static const unsigned short MAX_ARDUINO_PINS = 32;

public:
    ~ArduinoMockController();
    static ArduinoMockController & getInstance();

    typedef enum
    {
        REAL_TIMER_HANDLING,
        MANUAL_TIMER_HANDLING
    } TIMER_HANDLING;

    typedef enum
    {
        MANUAL_PIN_HANDLING
    } PIN_HANDLING;

    void setTimerMode( TIMER_HANDLING pTimerHandling );

    TIMER_HANDLING getTimerHandling() const;

    unsigned long getMicroSeconds() const;

    void setMicroSeconds( unsigned long microSeconds );

    unsigned long getMilliSeconds() const;

    void setMilliSeconds( unsigned long milliSeconds );

    void setPinMode( uint8_t pPinNumber, uint8_t pPinMode );

    void setPinValue( uint8_t pPinNumber, int pValue );

    int getPinValue( uint8_t pPinNumber );

private:
    ArduinoMockController();

    void initializeTimers();

    static ArduinoMockController *mInstance;

    TIMER_HANDLING mTimerHandling;

    unsigned long mMicroSeconds;

    unsigned long mMilliSeconds;

    timeb mInitialTime;

    struct timeval mInitialTimeVal;

    /**
     *  pin handling of the arduino mock class, at the moment only manual is supported
     */
    PIN_HANDLING mPinHandling;

    /**
     * holde the mode of each pin, could be INPUT or OUTPUT
     */
    uint8_t mPinMode[MAX_ARDUINO_PINS];

    /**
     * hold values of the arduino pins (values 0-1023). If pin is interpreted as digital
     * the values less than 512 are interpreted as LOW and and all values above as HIGH
     */
    int mPinValues[MAX_ARDUINO_PINS];
};



void ArduinoMockController::setTimerMode( TIMER_HANDLING pTimerHandling )
{
    mTimerHandling = pTimerHandling;
}

TIMER_HANDLING ArduinoMockController::getTimerHandling() const
{
    return mTimerHandling;
}

unsigned long ArduinoMockController::getMicroSeconds() const
{
    if (MANUAL_TIMER_HANDLING == getTimerHandling())
    {
        return mMicroSeconds;
    }
    else
    {
        struct timeval lTimeVal;

        if (gettimeofday( &lTimeVal, NULL ))
        {
            throw std::runtime_error( "Problem calling gettimeofday" );
        }

        return (lTimeVal.tv_sec - mInitialTimeVal.tv_sec) * 1000000 + (lTimeVal.tv_usec - mInitialTimeVal.tv_usec);
    }
}

void ArduinoMockController::setMicroSeconds( unsigned long microSeconds )
{
    mMicroSeconds = microSeconds;
}

unsigned long ArduinoMockController::getMilliSeconds() const
{
    if (MANUAL_TIMER_HANDLING == getTimerHandling())
    {
        return mMilliSeconds;
    }
    else
    {
        timeb lCurrent;
        ftime( &lCurrent );
        return (lCurrent.time - mInitialTime.time) * 1000 + (lCurrent.millitm - mInitialTime.millitm);
    }
}

void ArduinoMockController::setMilliSeconds( unsigned long milliSeconds )
{
    mMilliSeconds = milliSeconds;
}

#endif
