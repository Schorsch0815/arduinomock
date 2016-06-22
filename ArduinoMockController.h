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
  public:
    static const unsigned short MAX_ARDUINO_PINS = 32;

    static const int DIGITAL_LOW_HIGH_LIMIT = 650;

    static const int ANALOG_MIN_VALUE = 0;
    static const int ANALOG_MAX_VALUE = 1023;

    static const int PULSE_MIN_VALUE = 50;
    static const int PULSE_MAX_VALUE = 1500;

    static const int PULSE_NEUTRAL_VALUE;

    ~ArduinoMockController();
    static ArduinoMockController &getInstance();

    void reset();

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

    void setMicroSeconds( unsigned long pMicroSeconds );

    unsigned long getMilliSeconds() const;

    void setMilliSeconds( unsigned long pMilliSeconds );

    void delay( unsigned long pMilliSeconds );

    void delayMicroSeconds( unsigned long pMicroSeconds );

    inline void setPinSimulationMode( PIN_SIMULATION_MODE pPinSimulationMode );

    inline PIN_SIMULATION_MODE getPinSimulationMode() const;

    void setPinMode( uint8_t pPinNumber, uint8_t pPinMode );

    uint8_t getPinMode( uint8_t pPinNumber );

    void setDigitalValue( uint8_t pPinNumber, int pValue );
    void setAnalogValue( uint8_t pPinNumber, int pValue );
    void setPulseValue( uint8_t pPinNumber, int pValue );

    int getDigitalValue( uint8_t pPinNumber );
    int getAnalogValue( uint8_t pPinNumber );
    int getPulseValue( uint8_t pPinNumber, uint8_t pState, unsigned long pTimeout );

    void setAnalogReference( uint8_t pAnalogReferenceMode );

    uint8_t getAnalogReference() { return mAnalogReferenceMode; }

  private:
    ArduinoMockController();

    void initTimeHandling();

    void setPinValue( uint8_t pPinNumber, int pValue );

    int getPinValue( uint8_t pPinNumber );

    static ArduinoMockController sInstance;

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
     * the values less than 630 are interpreted as LOW and and all values above as HIGH
     */
    int mPinValues[MAX_ARDUINO_PINS];

    /**
     * hold values of the arduino pins if used with pulseIn. The default range is [1, 1500] default value is 750
     */
    int mPulseValues[MAX_ARDUINO_PINS];

    /**
     * holds analog reference mode see Arduino.h for possible values
     */
    int mAnalogReferenceMode;
};

void ArduinoMockController::setTimerMode( TIMER_SIMULATION_MODE pTimerMode )
{
    mTimerMode = pTimerMode;
    initTimeHandling();
}

ArduinoMockController::TIMER_SIMULATION_MODE ArduinoMockController::getTimerMode() const { return mTimerMode; }

void ArduinoMockController::setPinSimulationMode( PIN_SIMULATION_MODE pPinSimulationMode )
{
    mPinSimulationMode = pPinSimulationMode;
}

ArduinoMockController::PIN_SIMULATION_MODE ArduinoMockController::getPinSimulationMode() const
{
    return mPinSimulationMode;
}

#endif
