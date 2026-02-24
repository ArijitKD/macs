#include <stdio.h>
#include <string.h>
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
    serial_properties_t s_properties = { MACS_BAUDRATE, MACS_SERIAL_IO_TIMEOUT_MS };

    uint_t ports[PORT_MAX] = {0};

    uint_t active_ports_count = get_active_port_nos(ports, PORT_MAX);

    int macs_port = get_macs_port_no(ports, active_ports_count, &s_properties);

    if (macs_port == -1)
    {
        printf ("Error: No MACS device found!!!\n");
        return 1;
    }

    printf ("MACS device detected at port: COM%d\n", macs_port);

    serial_handle_t hserial = serial_open(macs_port, &s_properties);

    int bytes_wrote;
    int i = 0;
 
    while (i < 2)
    {
        bytes_wrote = serial_write(hserial, MACS_SET_ON, strlen(MACS_SET_ON));
        printf("Bytes wrote = %d\n", bytes_wrote);
        serial_wait(1000);
        bytes_wrote = serial_write(hserial, MACS_SET_OFF, strlen(MACS_SET_ON));
        printf("Bytes wrote = %d\n", bytes_wrote);
        i++;
    }

    serial_close(hserial);

    return 0;

}