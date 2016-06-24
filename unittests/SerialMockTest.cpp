/*--------------------------------------------------------------------
 * This file is part of the ArduinoMock library.
 *
 * RcCarLights is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RcCarLights is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RcCarLights.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright: Jochen Schales 2014
 *
 * --------------------------------------------------------------------*/

#include "gtest/gtest.h"

#include "../SerialMock.h"

using namespace std;

template <typename T>
void testSerialNumberPrintln( T pNumber, int pBase, const char *pExpectedOutput )
{
    testing::internal::CaptureStdout();
    Serial.println( pNumber, pBase );
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_STREQ( pExpectedOutput, output.c_str() );
}

template <typename T>
void testSerialAlphaPrintln( T pAlpha, const char *pExpectedOutput )
{
    testing::internal::CaptureStdout();
    Serial.println( pAlpha );
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_STREQ( pExpectedOutput, output.c_str() );
}

template <typename T>
void testSerialNumberPrint( T pNumber, int pBase, const char *pExpectedOutput )
{
    testing::internal::CaptureStdout();
    Serial.print( pNumber, pBase );
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_STREQ( pExpectedOutput, output.c_str() );
}

template <typename T>
void testSerialAlphaPrint( T pAlpha, const char *pExpectedOutput )
{
    testing::internal::CaptureStdout();
    Serial.print( pAlpha );
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_STREQ( pExpectedOutput, output.c_str() );
}

TEST( SerialMockTest, TestPrintln )
{
    Serial.begin( 9600 );

    testSerialAlphaPrintln( "Hello World", "Hello World\n" );
    testSerialAlphaPrintln( 'A', "A\n" );
    testSerialNumberPrintln( (unsigned char)255, DEC, "255\n" );
    testSerialNumberPrintln( (int)255, DEC, "255\n" );
    testSerialNumberPrintln( (int)-255, DEC, "-255\n" );
    testSerialNumberPrintln( (unsigned int)4000000, DEC, "4000000\n" );
    testSerialNumberPrintln( 10L, DEC, "10\n" );
    testSerialNumberPrintln( -10L, DEC, "-10\n" );
    testSerialNumberPrintln( (unsigned long)4000000000L, DEC, "4000000000\n" );
    testSerialNumberPrintln( 3.14152867, 2, "3.14\n" );
    testSerialNumberPrintln( 65535, HEX, "0000FFFF\n" );
    testSerialNumberPrintln( 65535, OCT, "00000177777\n" );
    testSerialNumberPrintln( 65535, BIN, "00000000000000001111111111111111\n" );
    testSerialNumberPrintln( -65535, HEX, "FFFF0001\n" );
    testSerialNumberPrintln( -65535, OCT, "77777600001\n" );
    testSerialNumberPrintln( -65535, BIN, "11111111111111110000000000000001\n" );
    Serial.end();
}

TEST( SerialMockTest, TestPrint )
{
    Serial.begin( 9600 );
    testSerialAlphaPrint( "Hello World", "Hello World" );
    testSerialAlphaPrint( 'A', "A" );
    testSerialNumberPrint( (unsigned char)255, DEC, "255" );
    testSerialNumberPrint( (int)255, DEC, "255" );
    testSerialNumberPrint( (int)-255, DEC, "-255" );
    testSerialNumberPrint( (unsigned int)4000000, DEC, "4000000" );
    testSerialNumberPrint( 10L, DEC, "10" );
    testSerialNumberPrint( -10L, DEC, "-10" );
    testSerialNumberPrint( (unsigned long)4000000000L, DEC, "4000000000" );
    testSerialNumberPrint( 3.14152867, 2, "3.14" );
    testSerialNumberPrint( 65535, HEX, "0000FFFF" );
    testSerialNumberPrint( 65535, OCT, "00000177777" );
    testSerialNumberPrint( 65535, BIN, "00000000000000001111111111111111" );
    testSerialNumberPrint( -65535, HEX, "FFFF0001" );
    testSerialNumberPrint( -65535, OCT, "77777600001" );
    testSerialNumberPrint( -65535, BIN, "11111111111111110000000000000001" );
    Serial.println( "" );
    Serial.end();
}

TEST( SerialMockTest, TestBeginEnd )
{
    Serial.begin( 9600, SERIAL_8N1 );
    Serial.end();
}

TEST( SerialMockTest, TestFlush )
{
    Serial.begin( 9600 );
    Serial.flush();
    Serial.end();
}

TEST( SerialMockTest, TestAvailable )
{
    Serial.begin( 9600 );
    EXPECT_EQ( 0, Serial.available() );
    Serial.end();
}

TEST( SerialMockTest, TestRead )
{
    Serial.begin( 9600 );
    EXPECT_EQ( -1, Serial.read() );
    Serial.end();
}

TEST( SerialMockTest, TestPeek )
{
    Serial.begin( 9600 );
    EXPECT_EQ( -1, Serial.peek() );
    Serial.end();
}

TEST( SerialMockTest, TestWrongIntegerBase )
{
    Serial.begin( 9600 );
    EXPECT_THROW( Serial.println( 65535, 47 ), range_error );
    Serial.end();
}
