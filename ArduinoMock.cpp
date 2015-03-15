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

#undef min
#undef max

#include <sys/timeb.h>
#include <iostream>
//#include <cstdlib>
//#include <sys/time.h>
//#include <cstdio>

#if defined(WIN32)
#include <windows.h>
#elif defined(__UNIX__)
#include <unistd.h>
#else
#endif

using namespace std;

static timeb & initializeTime();

static timeb sInitialTime = initializeTime();

timeb & initializeTime()
{
    ftime(&sInitialTime);
    return sInitialTime;
}

long millis()
{
    timeb lCurrent;
    ftime(&lCurrent);
    return (lCurrent.time - sInitialTime.time) * 1000 + (lCurrent.millitm - sInitialTime.millitm);
}

#include <windows.h>

void delay(long ms)
{
#if 0
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10*usec*1000); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
#endif
#if defined(WIN32)
    SetLastError(0);
    Sleep(ms);
    cerr << "Windows error:" << (GetLastError() ? -1 : 0) << endl;
#elif defined(LINUX)
    usleep(1000 * ms);
#else
#error ("no milli sleep available for platform")
    return -1;
#endif
}
