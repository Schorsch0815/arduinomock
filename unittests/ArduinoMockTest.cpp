/*
 * ArduinoMockControllerTest.cpp
 *
 *  Created on: 15.03.2015
 *      Author: Jochen
 */

#include "gtest/gtest.h"

#include <iostream>
#include "../Arduino.h"

using namespace std;

static unsigned long MILLI_SEC_DELAY_TEST = 200;
static unsigned long MILLI_SEC_DELAY_DEVIATION = 5;

static unsigned long MICRO_SEC_DELAY_TEST = 900;
static unsigned long MICRO_SEC_DELAY_DEVIATION = 300;

class ArduinoMockTest : public ::testing::Test
{
  protected:
    virtual void SetUp() { ArduinoMockController::getInstance().reset(); }

    virtual void TearDown() {}
};

TEST_F( ArduinoMockTest, RealMillisDelay )
{
    unsigned long t1 = millis();
    unsigned long t2 = millis();
    EXPECT_LE( t1, t2 );

    t1 = millis();
    delay( MILLI_SEC_DELAY_TEST );
    t2 = millis();
    EXPECT_LT( t1, t2 );
    EXPECT_LE( MILLI_SEC_DELAY_TEST, t2 - t1 );
    EXPECT_GT( MILLI_SEC_DELAY_DEVIATION, t2 - t1 - MILLI_SEC_DELAY_TEST );
    printf( "deviation = %lu\n", t2 - t1 - MILLI_SEC_DELAY_TEST );

    EXPECT_THROW( ArduinoMockController::getInstance().setMilliSeconds( 0 ), logic_error );
}

TEST_F( ArduinoMockTest, RealMicrosDelay )
{
    long t1 = micros();
    long t2 = micros();
    EXPECT_LE( t1, t2 );

    t1 = micros();
    delayMicroseconds( MICRO_SEC_DELAY_TEST );
    t2 = micros();
    EXPECT_LT( t1, t2 );
    EXPECT_LE( MICRO_SEC_DELAY_TEST, t2 - t1 );
    EXPECT_GT( MICRO_SEC_DELAY_DEVIATION, t2 - t1 - MICRO_SEC_DELAY_TEST );
    printf( "deviation = %lu\n", t2 - t1 - MICRO_SEC_DELAY_TEST );

    EXPECT_THROW( ArduinoMockController::getInstance().setMicroSeconds( 0 ), logic_error );
}

TEST_F( ArduinoMockTest, ManualMillisDelay )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );

    unsigned long t1 = millis();
    unsigned long t2 = millis();
    EXPECT_LE( t1, t2 );

    ArduinoMockController::getInstance().setMilliSeconds( 0 );
    t1 = millis();
    EXPECT_EQ( 0, t1 );

    unsigned long t1Micro = micros();
    EXPECT_EQ( 0, t1Micro );

    delay( 187 );
    t2 = millis();
    EXPECT_EQ( 187, t2 );

    unsigned long t2Micro = micros();
    EXPECT_EQ( 187000, t2Micro );

    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::REALTIME_TIMER_MODE );
}

TEST_F( ArduinoMockTest, ManualMicrosDelay )
{
    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::MANUAL_TIMER_MODE );

    unsigned long t1 = micros();
    unsigned long t2 = micros();
    EXPECT_LE( t1, t2 );

    ArduinoMockController::getInstance().setMicroSeconds( 0 );
    t1 = micros();
    EXPECT_EQ( 0, t1 );

    unsigned long t1Milli = millis();
    EXPECT_EQ( 0, t1Milli );

    delayMicroseconds( 1278 );
    t2 = micros();
    EXPECT_EQ( 1278, t2 );

    unsigned long t2Milli = millis();
    EXPECT_EQ( 1, t2Milli );

    ArduinoMockController::getInstance().setTimerMode( ArduinoMockController::REALTIME_TIMER_MODE );
}

TEST_F( ArduinoMockTest, Map )
{
    EXPECT_EQ( 0, map( 50, 50, 100, 0, 5 ) );

    EXPECT_EQ( -10, map( 50, 0, 100, -100, 80 ) );

    EXPECT_EQ( -5, map( -5, -100, 100, -10, 0 ) );

    EXPECT_EQ( 50, map( 50, 0, 100, 0, 100 ) );

    EXPECT_EQ( 50, map( 10, 0, 20, 0, 100 ) );

    EXPECT_EQ( 5, map( 99, 0, 99, 0, 5 ) );

    EXPECT_THROW( map( -10, 0, 100, -100, 80 ), range_error );

    EXPECT_THROW( map( 1, 10, 0, 0, 10 ), range_error );

    EXPECT_THROW( map( 1, 0, 10, 10, 0 ), range_error );

    EXPECT_THROW( map( 0, 0, 0, 0, 10 ), runtime_error );
}

TEST_F( ArduinoMockTest, DigitalPinValue )
{
    ArduinoMockController::getInstance().setPinSimulationMode( ArduinoMockController::MANUAL_PIN_MODE );
    EXPECT_THROW( ArduinoMockController::getInstance().setDigitalValue( -1, 0 ), range_error );
    EXPECT_THROW( ArduinoMockController::getInstance().setDigitalValue( 255, 0 ), range_error );

    EXPECT_THROW( ArduinoMockController::getInstance().getDigitalValue( -1 ), range_error );
    EXPECT_THROW( ArduinoMockController::getInstance().getDigitalValue( 255 ), range_error );
}

TEST_F( ArduinoMockTest, DigitalRead )
{
    ArduinoMockController::getInstance().setPinSimulationMode( ArduinoMockController::MANUAL_PIN_MODE );
    ArduinoMockController::getInstance().setDigitalValue( 0, LOW );
    EXPECT_EQ( LOW, digitalRead( 0 ) );
    ArduinoMockController::getInstance().setDigitalValue( 0, HIGH );
    EXPECT_EQ( HIGH, digitalRead( 0 ) );

    ArduinoMockController::getInstance().setAnalogValue( 0, ArduinoMockController::DIGITAL_LOW_HIGH_LIMIT - 1 );
    EXPECT_EQ( LOW, digitalRead( 0 ) );

    ArduinoMockController::getInstance().setAnalogValue( 0, ArduinoMockController::DIGITAL_LOW_HIGH_LIMIT );
    EXPECT_EQ( HIGH, digitalRead( 0 ) );

    EXPECT_THROW( digitalRead( -5 ), range_error );
    EXPECT_THROW( digitalRead( 32 ), range_error );
}

TEST_F( ArduinoMockTest, DigitalWrite )
{
    digitalWrite( 0, LOW );
    EXPECT_EQ( LOW, digitalRead( 0 ) );
    EXPECT_EQ( LOW, ArduinoMockController::getInstance().getDigitalValue( 0 ) );
    digitalWrite( 10, LOW );
    EXPECT_EQ( LOW, digitalRead( 10 ) );
    EXPECT_EQ( LOW, ArduinoMockController::getInstance().getDigitalValue( 10 ) );
    digitalWrite( 20, LOW );
    EXPECT_EQ( LOW, digitalRead( 20 ) );
    EXPECT_EQ( LOW, ArduinoMockController::getInstance().getDigitalValue( 20 ) );

    EXPECT_THROW( digitalWrite( 10, 255 ), range_error );
    EXPECT_THROW( digitalWrite( 10, -5 ), range_error );

    EXPECT_THROW( digitalWrite( -1, HIGH ), range_error );
    EXPECT_THROW( digitalWrite( 33, LOW ), range_error );
}

TEST_F( ArduinoMockTest, AnalogRead )
{
    ArduinoMockController::getInstance().setAnalogValue( 0, 0 );
    EXPECT_EQ( 0, analogRead( 0 ) );

    ArduinoMockController::getInstance().setAnalogValue( 10, 0 );
    EXPECT_EQ( 0, analogRead( 10 ) );

    ArduinoMockController::getInstance().setAnalogValue( 20, 0 );
    EXPECT_EQ( 0, analogRead( 20 ) );

    ArduinoMockController::getInstance().setAnalogValue( 10, 512 );
    EXPECT_EQ( 512, analogRead( 10 ) );

    ArduinoMockController::getInstance().setAnalogValue( 10, 1023 );
    EXPECT_EQ( 1023, analogRead( 10 ) );

    EXPECT_THROW( analogRead( -1 ), range_error );
    EXPECT_THROW( analogRead( 33 ), range_error );
}

TEST_F( ArduinoMockTest, AnalogWrite )
{
    analogWrite( 0, 0 );
    EXPECT_EQ( 0, analogRead( 0 ) );

    analogWrite( 10, 0 );
    EXPECT_EQ( 0, analogRead( 10 ) );

    analogWrite( 20, 0 );
    EXPECT_EQ( 0, analogRead( 20 ) );

    analogWrite( 10, 512 );
    EXPECT_EQ( 512, analogRead( 10 ) );

    analogWrite( 10, 1023 );
    EXPECT_EQ( 1023, analogRead( 10 ) );

    EXPECT_THROW( analogWrite( 10, 1024 ), range_error );
    EXPECT_THROW( analogWrite( 10, -5 ), range_error );

    EXPECT_THROW( analogWrite( -1, 0 ), range_error );
    EXPECT_THROW( analogWrite( 33, 0 ), range_error );
}

TEST_F( ArduinoMockTest, PinMode )
{
    pinMode( 0, 0 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 0 ), 0 );
    pinMode( 0, 1 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 0 ), 1 );
    pinMode( 10, 0 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 10 ), 0 );
    pinMode( 10, 1 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 10 ), 1 );
    pinMode( 20, 0 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 20 ), 0 );
    pinMode( 20, 1 );
    EXPECT_EQ( ArduinoMockController::getInstance().getPinMode( 20 ), 1 );

    // now the range tests for pin number
    EXPECT_THROW( pinMode( -1, 0 ), range_error );
    EXPECT_THROW( pinMode( 255, 0 ), range_error );

    // now the range tests for pin mode
    EXPECT_THROW( pinMode( 0, -1 ), range_error );
    EXPECT_THROW( pinMode( 0, 2 ), range_error );

    EXPECT_THROW( ArduinoMockController::getInstance().getPinMode( -1 ), range_error );
    EXPECT_THROW( ArduinoMockController::getInstance().getPinMode( 255 ), range_error );
}

TEST_F( ArduinoMockTest, PulseIn )
{
    EXPECT_EQ( (ArduinoMockController::PULSE_MAX_VALUE + ArduinoMockController::PULSE_MIN_VALUE) / 2, pulseIn( 0, LOW, 100 ) );

    ArduinoMockController::getInstance().setPulseValue(10,50);
    EXPECT_EQ( 50, pulseIn( 10, HIGH, 100 ) );

    ArduinoMockController::getInstance().setPulseValue(20,1500);
    EXPECT_EQ( 1500, pulseIn( 20, LOW, 100 ) );

    ArduinoMockController::getInstance().setPulseValue(20,1500);
    EXPECT_EQ( 1500, pulseIn( 20, HIGH, 100 ) );

    EXPECT_THROW( ArduinoMockController::getInstance().setPulseValue(33,500), range_error);

    EXPECT_THROW( pulseIn(33,LOW,1000), range_error);
    EXPECT_THROW( pulseIn(-1,LOW,1000), range_error);

    EXPECT_THROW( pulseIn(33,-1,1000), range_error);
    EXPECT_THROW( pulseIn(-1,30,1000), range_error);

    EXPECT_THROW( ArduinoMockController::getInstance().setPulseValue(0,ArduinoMockController::PULSE_MIN_VALUE - 1), range_error);
    EXPECT_THROW( ArduinoMockController::getInstance().setPulseValue(0,ArduinoMockController::PULSE_MAX_VALUE + 1), range_error);
}

TEST_F( ArduinoMockTest, AnalogReference )
{
    analogReference( DEFAULT );
    EXPECT_EQ( ArduinoMockController::getInstance().getAnalogReference(), DEFAULT );
    analogReference( EXTERNAL );
    EXPECT_EQ( ArduinoMockController::getInstance().getAnalogReference(), EXTERNAL );
    analogReference( INTERNAL );
    EXPECT_EQ( ArduinoMockController::getInstance().getAnalogReference(), INTERNAL );

    EXPECT_THROW( analogReference( 11 ), range_error );
}
