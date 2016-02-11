/*
 * ArduinoMockTest.cpp
 *
 *  Created on: 15.03.2015
 *      Author: Jochen
 */

#include "gtest/gtest.h"

#include <iostream>
#include "../ArduinoMock.h"

using namespace std;

static unsigned long MILLI_SEC_DELAY_TEST = 500;
static unsigned long MILLI_SEC_DELAY_DEVIATION = 5;

static unsigned long MICRO_SEC_DELAY_TEST = 900;
static unsigned long MICRO_SEC_DELAY_DEVIATION = 300;

GTEST_TEST(ArduinoMockTest,RealMillisDelay)
{
    unsigned long t1 = millis();
    unsigned long t2 = millis();
    EXPECT_LE(t1,t2);

    t1 = millis();
    delay(MILLI_SEC_DELAY_TEST);
    t2 = millis();
    EXPECT_LT(t1,t2);
    EXPECT_LE(MILLI_SEC_DELAY_TEST,t2-t1);
    EXPECT_GT(MILLI_SEC_DELAY_DEVIATION,t2-t1 - MILLI_SEC_DELAY_TEST);
    printf("deviation = %lu\n", t2-t1 - MILLI_SEC_DELAY_TEST );
}

GTEST_TEST(ArduinoMockTest,RealMicrosDelay)
{
    long t1 = micros();
    long t2 = micros();
    EXPECT_LE(t1,t2);

    t1 = micros();
    delayMicroseconds(MICRO_SEC_DELAY_TEST);
    t2 = micros();
    EXPECT_LT(t1,t2);
    EXPECT_LE(MICRO_SEC_DELAY_TEST,t2-t1);
    EXPECT_GT(MICRO_SEC_DELAY_DEVIATION,t2-t1 - MICRO_SEC_DELAY_TEST);
    printf("deviation = %lu\n", t2-t1 - MICRO_SEC_DELAY_TEST );
}

GTEST_TEST(ArduinoMockTest,ManualMillisDelay)
{
    ArduinoMock::getInstance().setTimerMode(ArduinoMock::MANUAL_TIMER_HANDLING);

    unsigned long t1 = millis();
    unsigned long t2 = millis();
    EXPECT_LE(t1,t2);

    ArduinoMock::getInstance().setMilliSeconds(0);
    t1 = millis();
    EXPECT_EQ(0,t1);
    ArduinoMock::getInstance().setMilliSeconds(187);
    t2 = millis();
    EXPECT_EQ(187,t2);
    ArduinoMock::getInstance().setTimerMode(ArduinoMock::REAL_TIMER_HANDLING);
}

GTEST_TEST(ArduinoMockTest,ManualMicrosDelay)
{
    ArduinoMock::getInstance().setTimerMode(ArduinoMock::MANUAL_TIMER_HANDLING);

    unsigned long t1 = micros();
    unsigned long t2 = micros();
    EXPECT_LE(t1,t2);

    ArduinoMock::getInstance().setMicroSeconds(0);
    t1 = micros();
    EXPECT_EQ(0,t1);
    ArduinoMock::getInstance().setMicroSeconds(278);
    t2 = micros();
    EXPECT_EQ(278,t2);
    ArduinoMock::getInstance().setTimerMode(ArduinoMock::REAL_TIMER_HANDLING);
}

TEST(ArduinoMocktest,Map)
{
    EXPECT_EQ(0,map(50,50,100,0,5));

    EXPECT_EQ(-10,map(50,0,100,-100,80));

    EXPECT_EQ(-5,map(-5,-100,100,-10,0));

    EXPECT_EQ(50,map(50,0,100,0,100));

    EXPECT_EQ(50,map(10,0,20,0,100));

    EXPECT_EQ(5,map(99,0,99,0,5));

    EXPECT_THROW(map(-10,0,100,-100,80),range_error);

    EXPECT_THROW(map(1,10,0,0,10),range_error);

    EXPECT_THROW(map(1,0,10,10,0),range_error);

    EXPECT_THROW(map(1,0,0,0,10),runtime_error);
}

TEST(ArduinoMocktest,DigitalRead)
{
    EXPECT_EQ(0,digitalRead(0));
    EXPECT_EQ(0,digitalRead(10));
    EXPECT_EQ(0,digitalRead(20));
}

TEST(ArduinoMocktest,DigitalWrite)
{
    digitalWrite(0,0);
    digitalWrite(10,0);
    digitalWrite(20,0);
}

TEST(ArduinoMocktest,AnalogRead)
{
    EXPECT_EQ(0,analogRead(0));
    EXPECT_EQ(0,analogRead(10));
    EXPECT_EQ(0,analogRead(20));
}

TEST(ArduinoMocktest,AnalogWrite)
{
    analogWrite(0,0);
    analogWrite(10,0);
    analogWrite(20,0);
}

TEST(ArduinoMocktest,PinMode)
{
    pinMode(0,0);
    pinMode(0,1);
    pinMode(10,0);
    pinMode(10,1);
    pinMode(20,0);
    pinMode(20,1);
}

TEST(ArduinoMocktest,PulseIn)
{
    EXPECT_EQ(0,pulseIn(0,0,100));
    EXPECT_EQ(0,pulseIn(10,0,100));
    EXPECT_EQ(0,pulseIn(20,0,100));
}

TEST(ArduinoMocktest,AnalogReference)
{
    analogReference(0);
    analogReference(10);
    analogReference(20);
}

