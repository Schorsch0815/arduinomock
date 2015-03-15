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

#include "ArduinoMock.h"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <exception>

//#include <cstring>
//#include <iostream>
//#include <iomanip>


SerialMock Serial;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

SerialMock::SerialMock()
{
}

SerialMock::~SerialMock()
{
}

void SerialMock::begin(unsigned long)
{
}
void SerialMock::begin(unsigned long, uint8_t)
{
}

void SerialMock::end()
{
}

int SerialMock::available(void)
{
    // no read operation supported by the mock
    return 0;
}

int SerialMock::peek(void)
{
    return -1;
}

int SerialMock::read(void)
{
    return -1;
}

// not supported yet
// int SerialMock::availableForWrite(void)
// {
//     return 0;
// }

void SerialMock::flush(void)
{
    fflush(stdout);
}

//size_t SerialMock::write(unsigned long n)
//{
//    return write((uint8_t) n);
//}
//inline size_t SerialMock::write(long n)
//{
//    return SerialMock::write((uint8_t) n);
//}
//inline size_t SerialMock::write(unsigned int n)
//{
//    return write((uint8_t) n);
//}
//inline size_t SerialMock::write(int n)
//{
//    return write((uint8_t) n);
//}

//    size_t print(const String &);

size_t SerialMock::print(const char pString[])
{
    return printf("%s", pString);
}

size_t SerialMock::print(char pChar)
{
    putchar(pChar);
    return 1;
}

size_t SerialMock::print(unsigned char pValue, int pBase)
{
    char lBuffer[4];
    return printf( "%s", convertNumber(pValue, pBase, lBuffer));
}

size_t SerialMock::print(int pValue, int pBase)
{
    return printf( (0 >= sgn(pValue)) ? "-" : "") + print(pValue*sgn(pValue),pBase);
}

size_t SerialMock::print(unsigned int pValue, int pBase)
{
    char lBuffer[10];
    return printf( "%s", convertNumber(pValue, pBase, lBuffer));
}

size_t SerialMock::print(long pValue, int pBase)
{
    return printf( (0 >= sgn(pValue)) ? "-" : "") + print(pValue*sgn(pValue),pBase);
}

size_t SerialMock::print(unsigned long pValue, int pBase)
{
    char lBuffer[20];
    return printf( "%s", convertNumber(pValue, pBase, lBuffer));
}

size_t SerialMock::print(double pValue, int pPrecision)
{
    return printf( "%.*lf", pPrecision, pValue);
}

//    size_t print(const Printable&);

//    size_t println(const String &s);
size_t SerialMock::println(const char pString[])
{
    return print(pString) + println();
}

size_t SerialMock::println(char pChar)
{
    return print(pChar) + println();
}

size_t SerialMock::println(unsigned char pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(int pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(unsigned int pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(long pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(unsigned long pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(double pValue, int pPrecision)
{
    return print(pValue, pPrecision) + println();
}

//    size_t println(const Printable&);
size_t SerialMock::println(void)
{
    return printf("\n");
}

char *SerialMock::convertNumber(unsigned long pNumber, int pBase, char *pBuffer)
{
    static char sBuffer[65];
    static char sHex[6] =
        { 'A', 'B', 'C', 'D', 'E', 'F' };
    unsigned int lShift;
    unsigned long lMask;
    int lValue;

    switch (pBase)
    {
        case BIN:
            lShift = 1;
            lMask = 1;
            break;
        case OCT:
            lShift = 3;
            lMask = 7;
            break;
        case HEX:
            lShift = 4;
            lMask = 15;
            break;
        case DEC:
            break;
        default:
            throw std::exception();
    }

    if (DEC != pBase)
    {
        sBuffer[64] = '\0';
        char *lStart = &(sBuffer[64]);
        for (unsigned int i = 63; i >= 0 && 0 != pNumber; --i, --lStart)
        {
            lValue = pNumber & lMask;
            pNumber >>= lShift;

            if (lValue < 10)
            {
                sBuffer[i] = '0' + lValue;
            }
            else
            {
                sBuffer[i] = sHex[lValue - 10];
            }
        }
        strcpy(pBuffer, lStart);
    }
    else
    {
        sprintf(pBuffer, "%lu", pNumber);
    }
    return pBuffer;
}
