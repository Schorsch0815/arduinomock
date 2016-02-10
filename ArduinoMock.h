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

#ifndef ARDUINO_MOCK_H
#define ARDUINO_MOCK_H

#include <cstdint>

#ifdef __cplusplus
extern "C"{
#endif

// need to be adapted according arduino settings
#define HIGH	0x1
#define LOW		0x0


#define INPUT 0x0
#define OUTPUT 0x1

// some defines from Arduino.h

#ifdef min
#undef min
#endif
#define min(a,b) ((a)<(b)?(a):(b))

#ifndef max
#undef max
#endif
#define max(a,b) ((a)>(b)?(a):(b))

typedef int myint_t;

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int word;

typedef unsigned char boolean;
typedef unsigned char byte;

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);

unsigned long millis();
unsigned long micros();
void delay(unsigned long pMilliseconds);
void delayMicroseconds(unsigned long pMicroseconds);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

long map(long pValue, long pFromLow, long pFromHigh, long pToLow, long pToHigh);

#ifdef __cplusplus
} // extern C
#endif

#endif
