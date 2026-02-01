#ifndef MACS_SERIAL_PORT_H
#define MACS_SERIAL_PORT_H

#include "types.h"

enum Port
{
    PORT_MAX_NAME = 7,
    PORT_MIN = 1,
    PORT_MAX = 256,
};

void get_active_port_nos(uint_t *ports_buf, uint_t ports_buf_size);

#endif