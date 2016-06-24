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

#ifndef SerialMock_h
#define SerialMock_h

#include <stdint.h>

enum
{
    DEC = 10,
    HEX = 16,
    OCT = 8,
    BIN = 2
};

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class SerialMock
{
public:
    SerialMock();

    virtual ~SerialMock();

    void begin( unsigned long );
    void begin( unsigned long, uint8_t );

    void end();

    virtual int available( void );

    virtual int peek( void );

    virtual int read( void );

    // not supported yet
    // int availableForWrite(void);

    virtual void flush( void );

    //    virtual size_t write(uint8_t);
    //
    //    size_t write(unsigned long n);
    //    size_t write(long n);
    //    size_t write(unsigned int n);
    //    size_t write(int n);

    //    size_t print(const String &);
    size_t print( const char[] );
    size_t print( char );
    size_t print( unsigned char, int = DEC );
    size_t print( int, int = DEC );
    size_t print( unsigned int, int = DEC );
    size_t print( long, int = DEC );
    size_t print( unsigned long, int = DEC );
    size_t print( double, int = 2 );
    //    size_t print(const Printable&);

    //    size_t println(const String &s);
    size_t println( const char[] );
    size_t println( char );
    size_t println( unsigned char, int = DEC );
    size_t println( int, int = DEC );
    size_t println( unsigned int, int = DEC );
    size_t println( long, int = DEC );
    size_t println( unsigned long, int = DEC );
    size_t println( double, int = 2 );
    //    size_t println(const Printable&);
    size_t println( void );

    operator bool()
    {
        return true;
    }

private:
    size_t print( long pNumber, int pBase, int pNumBits, bool pNewLine );
    size_t print( unsigned long pNumber, int pBase, int pNumBits, bool pNewLine );

    char convertDigit( int lValue );

    char *convertNumber( unsigned long pNumber, int pBase, int pNumBits, char *pBuffer, bool pNewLine );
    void determineShftAndMask( int pBase, unsigned int &lShift, unsigned long &lMask );

    static const int NUMBER_OF_BITS_FOR_LONG = sizeof( long ) * 8;
    static const int NUMBER_OF_BITS_FOR_INT = sizeof( int ) * 8;
    static const int NUMBER_OF_BITS_FOR_SHORT = sizeof( short ) * 8;
    static const int NUMBER_OF_BITS_FOR_CHAR = sizeof( char ) * 8;
};

extern SerialMock Serial;

#endif
