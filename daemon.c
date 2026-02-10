#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "serial/port.h"
#include "serial/io.h"
#include "serial/macs.h"


/*
int get_device_port(unsigned int *ports_buf, unsigned int ports_buf_size)
{
    unsigned int i;
    HANDLE hserial;
    char devpath[MAX_PATH];

    for (i = 0; i < ports_buf_size; ++i)
    {
        if (ports_buf[i] > PORT_MAX || ports_buf[i] < PORT_MIN)
            continue;   // Ignore illegal ports

        snprintf(devpath, MAX_PATH, "\\\\.\\COM%u", ports_buf[i]);
        hserial = CreateFile(
                            devpath, 
                            GENERIC_READ | GENERIC_WRITE, 
                            0, 
                            NULL, 
                            OPEN_EXISTING, 
                            FILE_ATTRIBUTE_NORMAL, 
                            NULL
                        );
        memset(devpath, 0, MAX_PATH);

        if (hserial == INVALID_HANDLE_VALUE)
            continue;

        DCB dcb = {0};
        dcb.DCBlength = sizeof(dcb);

        GetCommState(hserial, &dcb);

        dcb.BaudRate = CBR_9600;
        dcb.ByteSize = 8;
        dcb.StopBits = ONESTOPBIT;
        dcb.Parity   = NOPARITY;

        SetCommState(hserial, &dcb);

        ReadFile(hserial, buffer, size, &bytesRead, NULL);
        
    }
}
*/

int main(void)
{
    uint_t ports[PORT_MAX] = {0};

    get_active_port_nos(ports, sizeof(ports));

    for (uint_t i = 0; i < 10 && ports[i] > 0; ++i)
        printf ("COM%u\n", ports[i]);

    serial_properties_t s_properties = { 6, 9600, 300 };
    serial_handle_t hserial = serial_open(&s_properties);

    int bytes_wrote;
    int i = 0;
    while (i < 2)
    {
        bytes_wrote = serial_write(hserial, "1\n", 100);
        printf("Bytes wrote = %d\n", bytes_wrote);
        Sleep(1000);
        bytes_wrote = serial_write(hserial, "0\n", 100);
        printf("Bytes wrote = %d\n", bytes_wrote);
        i++;
    }

    char buf[11] = {0}; // store atmost 10 characters

    int bytes_read = serial_readline(hserial, buf, sizeof(buf));

    if (bytes_read == -1)
    {
        printf ("Serial read error!!!\n");
        return 1;
    }

    printf("String = \"%s\"\n", buf);
    printf("Bytes read = %d\n", bytes_read);

    serial_close(hserial);

    return 0;

}