#include <stdio.h>
#include <string.h>
#include "serial/port.h"
#include "serial/io.h"
#include "serial/macs.h"


int main(int argc, char *argv[])
{
    uint_t status_on = 1;
    if (argc > 1 && strcmp(argv[1], "off") == 0)
    {
        printf ("New state = OFF\n");
        status_on = 0;
    }
    else if (argc > 1 && strcmp(argv[1], "on") == 0)
    {
        printf ("New state = ON\n");
    }
    else
    {
        printf ("Bad flag or no flag (only \'on\' or \'off\' accepted).\n");
        return 1;
    }
    serial_properties_t s_properties = { MACS_BAUDRATE, MACS_SERIAL_IO_TIMEOUT_MS };
    uint_t ports[PORT_MAX] = {0};
    uint_t active_ports_count = get_active_port_nos(ports, PORT_MAX);
    int macs_port = get_macs_port_no(ports, active_ports_count, &s_properties);

    if (macs_port == -1)
    {
        printf ("Error: No MACS device found!!!\nFailed to change state.\n");
        return 1;
    }
    printf ("MACS device detected at port: COM%d\n", macs_port);

    serial_handle_t hserial = serial_open(macs_port, &s_properties);
    int bytes_wrote;

    if (status_on)
        bytes_wrote = serial_write(hserial, MACS_SET_ON, MACS_ON_OFF_WRITE_SIZE);
    else
        bytes_wrote = serial_write(hserial, MACS_SET_OFF, MACS_ON_OFF_WRITE_SIZE);

    printf("Bytes wrote = %d\n", bytes_wrote);
    serial_close(hserial);

    return 0;
}