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
        REALTIME_TIMER_MODE,
        MANUAL_TIMER_MODE
    } TIMER_SIMULATION_MODE;

    typedef enum
    {
        MANUAL_PIN_MODE
    } PIN_SIMULATION_MODE;

    inline void setTimerMode( TIMER_SIMULATION_MODE pTimerMode );

    inline TIMER_SIMULATION_MODE getTimerMode() const;

    unsigned long getMicroSeconds() const;

    inline void setMicroSeconds( unsigned long microSeconds );

    unsigned long getMilliSeconds() const;

    inline void setMilliSeconds( unsigned long milliSeconds );

    inline void setPinSimulationMode( PIN_SIMULATION_MODE pPinSimulationMode );

    inline PIN_SIMULATION_MODE getPinSimulationMode() const;

    void setPinMode( uint8_t pPinNumber, uint8_t pPinMode );

    uint8_t getPinMode( uint8_t pPinNumber );

    void setPinValue( uint8_t pPinNumber, int pValue );

    int getPinValue( uint8_t pPinNumber );

private:
    ArduinoMockController();

    void initializeTimers();

    static ArduinoMockController *mInstance;

    TIMER_SIMULATION_MODE mTimerMode;

    unsigned long mMicroSeconds;

    unsigned long mMilliSeconds;

    timeb mInitialTime;

    struct timeval mInitialTimeVal;

    /**
     *  simulation mode of pins of the arduino mock class, at the moment only manual is supported
     */
    PIN_SIMULATION_MODE mPinSimulationMode;

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



void ArduinoMockController::setTimerMode( TIMER_SIMULATION_MODE pTimerMode )
{
    mTimerMode = pTimerMode;
}

ArduinoMockController::TIMER_SIMULATION_MODE ArduinoMockController::getTimerMode() const
{
    return mTimerMode;
}

void ArduinoMockController::setMicroSeconds( unsigned long microSeconds )
{
    mMicroSeconds = microSeconds;
}

void ArduinoMockController::setMilliSeconds( unsigned long milliSeconds )
{
    mMilliSeconds = milliSeconds;
}


void ArduinoMockController::setPinSimulationMode( PIN_SIMULATION_MODE pPinSimulationMode )
{
    mPinSimulationMode = pPinSimulationMode;
}


ArduinoMockController::PIN_SIMULATION_MODE ArduinoMockController::getPinSimulationMode() const
{
    return mPinSimulationMode;
}



#endif
