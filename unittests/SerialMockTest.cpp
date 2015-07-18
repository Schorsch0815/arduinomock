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

TEST(SerialMockTest,TestPrint)
{
    Serial.begin(9600);
    Serial.println(255);
    Serial.println(-255);
    Serial.println(10L);
    Serial.println(-10L);
    Serial.println(3.14152867);
    Serial.println(65535,HEX);
    Serial.println(65535,OCT);
    Serial.println(65535,BIN);
    Serial.println(-65535,HEX);
    Serial.println(-65535,OCT);
    Serial.println(-65535,BIN);
}
