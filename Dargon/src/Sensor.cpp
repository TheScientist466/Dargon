#include <stdlib.h>
#include <stdio.h>
#include <mutex>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"

static int sensorVal = 0;
static bool toTerminate = false;
std::mutex mtx;

int getSensorVal() {
    return sensorVal;
}

void terminate() {
    toTerminate = true;
}

void pollSensorVal()
{
    int i, n,
        cport_nr = 4,        /* /dev/ttyS0 (COM1 on windows) */
        bdrate = 9600;       /* 9600 baud */

    unsigned char buf[4];

    char mode[] = {'8','N','1',0};


    if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
    {
        printf("Can not open comport5n");
        return;
    }
    while(true)
    {
        mtx.lock();
        if(toTerminate) {
            mtx.unlock();
            return;
        }
        n = RS232_PollComport(cport_nr, buf, 4);

        if(n > 0)
        {
            sensorVal = buf[0];
        }
        mtx.unlock();

#ifdef _WIN32
        Sleep(12);
#else
        usleep(100000);  /* sleep for 100 milliSeconds */
#endif
    }
    RS232_CloseComport(cport_nr);
}