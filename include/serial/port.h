/**
 * \file port.h
 *
 * \brief This header contains serial port-specific enumerations and functions.
 */

#ifndef MACS_SERIAL_PORT_H
#define MACS_SERIAL_PORT_H

#include "types.h"

/** \brief Enumeration to store generic port-related constants.*/
enum Port
{
    PORT_NAMELEN_MAX = 7,   /**< Maximum port name length (including port path) */
    PORT_MIN = 1,           /**< Lowest possible serial port number */
    PORT_MAX = 256          /**< Highest possible serial port number */
};

/**
 * \brief Get all active serial ports.
 *
 * Gives an array containing the indices of all active serial (COM) ports.
 * Internally, queries all available COM ports from PORT_MIN to PORT_MAX using
 * Win32 QueryDosDevice() to determine whether a given COM port is active.
 *
 * \param[out] ports Pointer to a buffer to store the active COM port numbers.
 * \param ports_count Number of ports to check for, where checking occurs serially.
 *
 * \return The number of active ports found in the range PORT_MIN<=port<=ports_count.
 */
uint_t get_active_port_nos(uint_t *ports, uint_t ports_count);

#endif