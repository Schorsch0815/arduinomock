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

TEST(ArduinoMockTest,MillisDelay)
{
    long t1 = millis();
    long t2 = millis();
    EXPECT_LE(t1,t2);

    t1 = millis();
    delay(500);
    t2 = millis();
    EXPECT_LE(500,t2-t1);
}


TEST(ArduinoMocktest,Map)
{
    EXPECT_EQ(50,map(50,0,100,0,100));

    EXPECT_EQ(50,map(10,0,20,0,100));

    EXPECT_EQ(5,map(99,0,99,0,5));

    EXPECT_EQ(5,map(99,0,99,0,5));

    EXPECT_THROW(map(1,10,0,0,10),range_error);

    EXPECT_THROW(map(1,0,10,10,0),range_error);

    EXPECT_THROW(map(1,0,0,0,10),runtime_error);
}

