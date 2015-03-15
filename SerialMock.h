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

#ifndef SerialMock_h
#define SerialMock_h

#include <cstdlib>
#include <stdint.h>


enum
{
    DEC = 10, HEX = 16, OCT = 8, BIN = 2
};

class SerialMock
{
public:
    SerialMock();

    virtual ~SerialMock();

    void begin(unsigned long);
    void begin(unsigned long, uint8_t);

    void end();

    virtual int available(void);

    virtual int peek(void);

    virtual int read(void);

    // not supported yet
    // int availableForWrite(void);

    virtual void flush(void);

//    virtual size_t write(uint8_t);
//
//    size_t write(unsigned long n);
//    size_t write(long n);
//    size_t write(unsigned int n);
//    size_t write(int n);

//    size_t print(const String &);
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);
//    size_t print(const Printable&);

//    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
//    size_t println(const Printable&);
    size_t println(void);

    operator bool()
    {
        return true;
    }

private:
    char *convertNumber(unsigned long pNumber, int pBase, char *pBuffer);

};

extern SerialMock Serial;

#endif