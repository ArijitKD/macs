#ifndef MACS_SERIAL_MACS_H
#define MACS_SERIAL_MACS_H

#include "types.h"
#include "devices.h"

#define MACS_DEVICE_NAME			"MACS001"
#define MACS_REPLY_LINE				"MACS001\r\n"
#define MACS_REPLY_LINE_SIZE         9
#define MACS_DEVICE_TYPE            RASPBERRY_PI_PICO

#define MACS_SET_ON					"1\n"
#define MACS_SET_OFF				"0\n"
#define MACS_ON_OFF_WRITE_SIZE      2
#define MACS_MAX_RX_READ_TRIES      5
#define MACS_MAX_TX_WRITE_TRIES     3

#define MACS_BAUDRATE				9600
#define MACS_SERIAL_IO_TIMEOUT_MS	300

#define MACS_ERR_NO_DEVICE          -2
#define MACS_ERR_WRITE_FAILURE      -3

#define MACS_STATE_ON               1
#define MACS_STATE_OFF              0

int get_macs_port_no(uint_t *active_ports, uint_t active_ports_count, serial_properties_t *s_properties);
void update_macs_state(uint_t state, int *macs_port, int *errcode);

#endif