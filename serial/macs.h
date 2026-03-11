/**
 * \file macs.h
 *
 * \brief Main include header, contains all macros and functions specific to the MACS device.
 *
 * Usually, this header is all that should be required to be included in the main
 * source files.
 *
 */

#ifndef MACS_SERIAL_MACS_H
#define MACS_SERIAL_MACS_H

#include "types.h"
#include "devices.h"
#include "errcodes.h"   // To allow error code checks in the main source files

#define MACS_DEVICE_NAME			"MACS001"           /**< \brief Internal name tag/serial number of the MACS device */
#define MACS_REPLY_LINE				"MACS001\r\n"       /**< \brief String that the device replies with periodically */
#define MACS_REPLY_LINE_SIZE         9                  /**< \brief Size of the reply string */
#define MACS_DEVICE_TYPE            RASPBERRY_PI_PICO   /**< \brief Type of the device as in devices.h (required for soft-reboot) */

#define MACS_SET_ON					"1\n"               /**< \brief Written to the device to set it to ON */
#define MACS_SET_OFF				"0\n"               /**< \brief Written to the device to set it to OFF */
#define MACS_ON_OFF_WRITE_SIZE      2                   /**< \brief Size of the strings that are written to change device state */
#define MACS_MAX_RX_READ_TRIES      5                   /**< \brief Maximum read attempts before a read failure is triggered */
#define MACS_MAX_TX_WRITE_TRIES     3                   /**< \brief Maximum write attempts before a write failure is triggered */

#define MACS_BAUDRATE				9600                /**< \brief Baud rate used for the serial UART communication */
#define MACS_SERIAL_IO_TIMEOUT_MS	300                 /**< \brief Timeout for read/write functions in case device stops responding */

#define MACS_STATE_ON               1                   /**< \brief Macro to test ON state of the device */
#define MACS_STATE_OFF              0                   /**< \brief Macro to test OFF state of the device */


/**
 * \brief Get the port number to which the MACS device is connected.
 *
 * \param[in] active_ports Pointer to a buffer containing a list of all active port numbers.
 * \param active_ports_count Number of active ports (Size of the active_ports buffer).
 * \param[in] s_properties Pointer to a structure containing the serial connection properties
 * (baud rate and read-write timeout).
 *
 * \return The port to which the MACS device is connected, or -1 in case the device is not found
 * among all active ports.
 */
int get_macs_port_no(uint_t *active_ports, uint_t active_ports_count, serial_properties_t *s_properties);


/**
 * \brief Updates the MACS device state as specified (ON or OFF).
 *
 * \param state New state (MACS_STATE_ON or MACS_STATE_OFF).
 * \param[out] macs_port Pointer to a variable to which the MACS port may be saved.
 * \param[out] errcode Pointer to a variable to which the error code may be saved.
 */
void update_macs_state(uint_t state, int *macs_port, int *errcode);
 
#endif