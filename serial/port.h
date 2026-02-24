#ifndef MACS_SERIAL_PORT_H
#define MACS_SERIAL_PORT_H

#include "types.h"

enum Port
{
    PORT_NAMELEN_MAX = 7,
    PORT_MIN = 1,
    PORT_MAX = 256
};

uint_t get_active_port_nos(uint_t *ports, uint_t ports_count);

#endif