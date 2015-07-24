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

GTEST_TEST(ArduinoMockTest,MillisDelay)
{
    unsigned long t1 = millis();
    unsigned long t2 = millis();
    EXPECT_LE(t1,t2);

    t1 = millis();
    delay(MILLI_SEC_DELAY_TEST);
    t2 = millis();
    EXPECT_LE(MILLI_SEC_DELAY_TEST,t2-t1);
    EXPECT_GT(MILLI_SEC_DELAY_DEVIATION,t2-t1 - MILLI_SEC_DELAY_TEST);
    printf("deviation = %lu\n", t2-t1 - MILLI_SEC_DELAY_TEST );
}

GTEST_TEST(ArduinoMockTest,MicrosDelay)
{
    long t1 = micros();
    long t2 = micros();
    EXPECT_LE(t1,t2);

    t1 = micros();
    delayMicroseconds(MICRO_SEC_DELAY_TEST);
    t2 = micros();
    EXPECT_LE(MICRO_SEC_DELAY_TEST,t2-t1);
    EXPECT_GT(MICRO_SEC_DELAY_DEVIATION,t2-t1 - MICRO_SEC_DELAY_TEST);
    printf("deviation = %lu\n", t2-t1 - MICRO_SEC_DELAY_TEST );
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

