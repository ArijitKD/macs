#include <string.h>
#include "serial/port.h"
#include "serial/io.h"
#include "macs.h"
#include "errcodes.h"


int get_macs_port_no(uint_t *active_ports, uint_t active_ports_count, serial_properties_t *s_properties)
{
	serial_handle_t hserial;
	uint_t max_read_tries = MACS_MAX_RX_READ_TRIES;

	char reply_line[MACS_REPLY_LINE_SIZE + 1] = {0};
	int bytes_read;

	for (uint_t i = 0; i < active_ports_count; ++i)
	{
		hserial = serial_open(active_ports[i], &(*s_properties));

		for (uint_t j = 0; j < max_read_tries; ++j)
		{
			bytes_read = serial_readline(hserial, reply_line, sizeof(reply_line));

			if (bytes_read != -1 && strcmp(MACS_REPLY_LINE, reply_line) == 0)
			{
				serial_close(hserial);
				return active_ports[i];

			}
			memset(reply_line, 0, MACS_REPLY_LINE_SIZE);
		}

		serial_close(hserial);
		memset(reply_line, 0, MACS_REPLY_LINE_SIZE);
	}

	return -1;
}


void update_macs_state(uint_t state, int *macs_port, int *errcode)
{
	*errcode = 0;
	serial_properties_t s_properties = { MACS_BAUDRATE, MACS_SERIAL_IO_TIMEOUT_MS };
    uint_t ports[PORT_MAX] = {0};
    uint_t active_ports_count = get_active_port_nos(ports, PORT_MAX);
    *macs_port = get_macs_port_no(ports, active_ports_count, &s_properties);

	if (*macs_port == -1)
    {
        *errcode = MACS_ERR_NO_DEVICE;
        return;
    }

	serial_handle_t hserial = serial_open(*macs_port, &s_properties);
    int bytes_wrote = 0;
	uint_t i = 0;

    do
    {
        if (state == MACS_STATE_ON)
            bytes_wrote = serial_write(hserial, MACS_SET_ON, MACS_ON_OFF_WRITE_SIZE);
        else
            bytes_wrote = serial_write(hserial, MACS_SET_OFF, MACS_ON_OFF_WRITE_SIZE);
        i++;
    }   while ((bytes_wrote == -1 || bytes_wrote < MACS_ON_OFF_WRITE_SIZE) &&
        (i < MACS_MAX_TX_WRITE_TRIES));
	
	if (i == MACS_MAX_TX_WRITE_TRIES)
	{
		*errcode = MACS_ERR_WRITE_FAILURE;
	}
    serial_close(hserial);
}