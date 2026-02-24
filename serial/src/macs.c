#include <string.h>
#include "../macs.h"

int get_macs_port_no(uint_t *active_ports, uint_t active_ports_count, serial_properties_t *s_properties)
{
	serial_handle_t hserial;
	uint_t max_read_tries = 3;

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