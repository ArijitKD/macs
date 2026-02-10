#ifndef MACS_SERIAL_MACS_H
#define MACS_SERIAL_MACS_H

#include "io.h"
#include "port.h"

#define MACS_DEVICE_NAME	"MACS001"
#define MACS_REPLY_STR	"MACS001"

uint_t get_macs_port_no(uint_t* active_ports_buf, uint_t active_ports_buf_size, serial_properties_t* s_properties);

#endif