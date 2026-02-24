#include <windows.h>
#include <stdio.h>
#include "../port.h"

uint_t get_active_port_nos(uint_t *ports, uint_t ports_count)
{
    char port_name[PORT_NAMELEN_MAX];
    char port_path[MAX_PATH];
    uint_t i, m = 0;

    for (i = PORT_MIN; i <= PORT_MAX && m < ports_count; ++i)
    {
        snprintf(port_name, PORT_NAMELEN_MAX, "COM%u", i);
        if (QueryDosDevice(port_name, port_path, MAX_PATH))
            ports[m++] = i;
        memset(port_name, 0, PORT_NAMELEN_MAX);
    }
    return m;   // Return the number of active ports
}