/**
 * \file io.h
 *
 * \brief This header contains functions for serial I/O operations.
 *
 */

#ifndef MACS_SERIAL_IO_H
#define MACS_SERIAL_IO_H

#include "types.h"


/**
 * \brief Suspend host execution.
 *
 * Halts the host-side execution for given amount of time (in milliseconds).
 * Internally, calls Win32 API's Sleep().
 *
 * \param time_ms The delay duration in milliseconds.
 */
void serial_wait(uint_t time_ms);


/**
 * \brief Performs a "soft-reboot" of the device.
 *
 * Triggers a soft-reboot/resets the MACS device. Not all devices reset
 * in the same way, therefore this function may not work properly unless the
 * device is supported. See devices.h for list of supported devices. The
 * desired device type is set by changing the macro MACS_DEVICE_TYPE in macs.h.
 *
 * \param hserial The handle to the serial device.
 */
void serial_reset(serial_handle_t hserial);


/**
 * \brief Opens a serial port in read-write mode.
 *
 * Opens a given serial port in read-write mode, with specified properties.
 *
 * \param port_no The port where the device is connected (1<=port<=256).
 * \param[in] s_properties Pointer to a structure that defines the properties
 * of the serial connection (baud rate & read-write timeout in milliseconds).
 *
 * \return An open serial device handle on success, or NULL on failure.
 */
serial_handle_t serial_open(uint_t port_no, serial_properties_t *s_properties);


/**
 * \brief Reads incoming data from a serial device port.
 *
 * Reads incoming data from an open serial device handle and copies it into a
 * specified buffer.
 *
 * \param hserial Handle to an open serial device.
 * \param[out] buf Pointer to a buffer to store the read data.
 * \param count Number of bytes to read (MUST be at least 1 byte less than
 * the buffer size to account for null terminator in ASCII strings).
 *
 * \return The number of bytes successfully read (0<=bytes<=count) or
 * -1 on failure.
 */
int serial_read(serial_handle_t hserial, char *buf, uint_t count);


/**
 * \brief Writes given data to a serial device port.
 *
 * Writes given data to an open device handle from a specified buffer.
 *
 * \param hserial Handle to an open serial device object.
 * \param[in] buf Pointer to a buffer containing the write data (ASCII string).
 * \param count Number of bytes to write (SHOULD be 0<=count<=strlen(buf)).
 *
 * \return The number of bytes successfully written (which might be
 * either equal to less than count) or -1 on failure.
 */
int serial_write(serial_handle_t hserial, char *buf, uint_t count);


/**
 * \brief Closes an open serial device handle.
 *
 * Closes an open serial device handle after stopping all reads/writes and
 * clearing the TX/RX buffers.
 *
 * \param hserial Handle to an open serial device object.
 *
 **/
void serial_close(serial_handle_t hserial);


/**
 * \brief Reads incoming data from a serial device port upto the first '\\n'.
 *
 * Reads incoming data from a serial device port upto the first '\n'. Uses
 * serial_read() internally.
 *
 * \param hserial Handle to an open serial device object.
 * \param[out] buf Pointer to a buffer to store the read data.
 * \param buf_len Size of the buffer.
 *
 * \return The line size, or -1 in case the buffer gets filled up before a '\\n'
 * is found.
 
 * \note The last byte is always reserved for '\0'. Hence, only buf_len - 1 bytes
 * would, atmost, be modified in any case.
 */
int serial_readline(serial_handle_t hserial, char *buf, uint_t buf_len);


/**
 * \brief Writes data from a buffer to a serial device port upto the first
 * '\\n' in the same.
 *
 * \note This is a dummy function and needs to be updated.
 *
 * \return -1 in any case as of now.
 */
int serial_writeline(serial_handle_t hserial, char *buf, uint_t buf_len);

#endif