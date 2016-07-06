/*
 * Adafruit_NeoPixelTest.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ejocsch
 */

#include "gtest/gtest.h"

#include <iostream>
#include "../Adafruit_NeoPixel/Adafruit_NeoPixel.h"

using namespace std;

class Adafruit_NeoPixelMockTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        ArduinoMockController::getInstance().reset();
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Adafruit_NeoPixelMockTest, ionitialization)
{
	Adafruit_NeoPixel neo(3,1);

	EXPECT_EQ(0,neo.getPixelColor(0));
	EXPECT_EQ(0,neo.getPixelColor(1));
	EXPECT_EQ(0,neo.getPixelColor(2));
	EXPECT_EQ(0,neo.getPixelColor(3));
}

TEST_F(Adafruit_NeoPixelMockTest, setPixelColor)
{
	Adafruit_NeoPixel neo(10,1);

	neo.setPixelColor(1,255,248,12);
	neo.setPixelColor(9,255,255,255);

	EXPECT_EQ(0,neo.getPixelColor(0));
	EXPECT_EQ(0xfff80c,neo.getPixelColor(1));
	EXPECT_EQ(0,neo.getPixelColor(2));
	EXPECT_EQ(0,neo.getPixelColor(3));
	EXPECT_EQ(0,neo.getPixelColor(4));
	EXPECT_EQ(0,neo.getPixelColor(5));
	EXPECT_EQ(0,neo.getPixelColor(6));
	EXPECT_EQ(0,neo.getPixelColor(7));
	EXPECT_EQ(0,neo.getPixelColor(8));
	EXPECT_EQ(0xffffff,neo.getPixelColor(9));
}

TEST_F(Adafruit_NeoPixelMockTest, getPixelOutOfRange)
{
	Adafruit_NeoPixel neo(10,1);

	EXPECT_EQ(0,neo.getPixelColor(6000));
}


