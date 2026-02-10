#ifndef MACS_SERIAL_IO_H
#define MACS_SERIAL_IO_H

#include "port.h"
#include "types.h"

void serial_reset(serial_handle_t hserial);
serial_handle_t serial_open(uint_t port_no, serial_properties_t *s_properties);
int serial_read(serial_handle_t hserial, char *buf, uint_t count);
int serial_write(serial_handle_t hserial, char *buf, uint_t count);
void serial_close(serial_handle_t hserial);
int serial_readline(serial_handle_t hserial, char *buf, uint_t buf_len);
int serial_writeline(serial_handle_t hserial, char *buf, uint_t buf_len);

#endif