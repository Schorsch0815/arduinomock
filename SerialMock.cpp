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

#include "ArduinoMock.h"
#include "SerialMock.h"

#include <cstdio>
#include <cstring>
#include <stdexcept>

using namespace std;

SerialMock Serial;

template<typename T>
    int sgn(T val)
    {
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
    return print((unsigned long) pValue, pBase, NUMBER_OF_BITS_FOR_CHAR, false);
}

size_t SerialMock::print(int pValue, int pBase)
{
    return print((long) pValue, pBase, NUMBER_OF_BITS_FOR_INT, false);
}

size_t SerialMock::print(unsigned int pValue, int pBase)
{
    return print((unsigned long) pValue, pBase, NUMBER_OF_BITS_FOR_LONG, false);
}

size_t SerialMock::print(long pValue, int pBase)
{
    return print(pValue, pBase, NUMBER_OF_BITS_FOR_LONG, false);
}

size_t SerialMock::print(unsigned long pValue, int pBase)
{
    return print(pValue, pBase, NUMBER_OF_BITS_FOR_LONG, false);
}

size_t SerialMock::print(double pValue, int pPrecision)
{
    return printf("%.*lf", pPrecision, pValue);
}

//    size_t print(const Printable&);

//    size_t println(const String &s);

size_t SerialMock::println(const char pString[])
{
    return printf("%s\n", pString);
}

size_t SerialMock::println(char pChar)
{
    return printf("%c\n", pChar);
}

size_t SerialMock::println(unsigned char pValue, int pBase)
{
    return print(pValue, pBase) + println();
}

size_t SerialMock::println(int pValue, int pBase)
{
    return print((long) pValue, pBase, NUMBER_OF_BITS_FOR_INT, true);
}

size_t SerialMock::println(unsigned int pValue, int pBase)
{
    return print((unsigned long) pValue, pBase, NUMBER_OF_BITS_FOR_INT, true);
}

size_t SerialMock::println(long pValue, int pBase)
{
    return print(pValue, pBase, NUMBER_OF_BITS_FOR_LONG, true);
}

size_t SerialMock::println(unsigned long pValue, int pBase)
{
    return print(pValue, pBase, NUMBER_OF_BITS_FOR_LONG, true);
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

size_t SerialMock::print(long pNumber, int pBase, int pNumBits, bool pNewLine)
{
    char lBuffer[100];

    if (pBase == DEC)
    {
        return printf(
                "%s%s",
                (0 > sgn(pNumber)) ? "-" : "",
                convertNumber(((unsigned long) pNumber * sgn(pNumber)), pBase,
                              pNumBits, lBuffer, pNewLine));
    }
    else
    {
        return printf(
                "%s",
                convertNumber((unsigned long) pNumber, pBase, pNumBits, lBuffer,
                              pNewLine));
    }
}

size_t SerialMock::print(unsigned long pNumber, int pBase, int pNumBits,
                         bool pNewLine)
{
    char lBuffer[100];

    return printf("%s",
                  convertNumber(pNumber, pBase, pNumBits, lBuffer, pNewLine));
}

void SerialMock::determineShftAndMask(int pBase, unsigned int& lShift,
                                      unsigned long & lMask)
{
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
}

char SerialMock::convertDigit(int lValue)
{
    static char sHex[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };

    if (lValue < 10)
    {
        return '0' + lValue;
    }
    else
    {
        return sHex[lValue - 10];
    }
}

char *SerialMock::convertNumber(unsigned long pNumber, int pBase, int pNumBits,
                                char *pBuffer, bool pNewLine)
{
    static char sBuffer[65];
    unsigned int lShift;
    unsigned long lMask;

    determineShftAndMask(pBase, lShift, lMask);

    if (DEC != pBase)
    {
        int lPos = pNumBits / lShift +(0 != (pNumBits % lShift));
        sBuffer[lPos] = '\0';
        char *lStart = &(sBuffer[lPos-1]);
        for (int i = lPos-1; i >= 0; --i, --lStart)
        {
            int lValue = pNumber & lMask;
            pNumber >>= lShift;

            sBuffer[i] = convertDigit(lValue);
       }

        strcpy(pBuffer, ++lStart);
        if (pNewLine)
        {
            strcat(pBuffer, "\n");
        }
    }
    else
    {
        sprintf(pBuffer, "%lu%s", pNumber, (pNewLine ? "\n" : ""));
    }
    return pBuffer;
}
