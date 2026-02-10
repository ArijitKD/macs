#ifndef MACS_SERIAL_TYPES_H
#define MACS_SERIAL_TYPES_H

typedef unsigned int uint_t;
typedef long unsigned int luint_t;
typedef void* serial_handle_t;
typedef struct
{
	uint_t baud_rate;
	uint_t timeout_ms;
} serial_properties_t;

#endif