#include <windows.h>
#include <stdio.h>
#include "../port.h"

void get_active_port_nos(uint_t *ports_buf, uint_t ports_buf_size)
{
    char port_name[PORT_NAMELEN_MAX];
    char port_path[MAX_PATH];
    uint_t i, m = 0;

    for (i = PORT_MIN; i <= PORT_MAX && m < ports_buf_size; ++i)
    {
        snprintf(port_name, PORT_NAMELEN_MAX, "COM%u", i);
        if (QueryDosDevice(port_name, port_path, MAX_PATH))
            ports_buf[m++] = i;
        memset(port_name, 0, PORT_NAMELEN_MAX);
    }
}