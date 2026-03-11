/**
 * \file types.h
 *
 * \brief This header contains data-types specific to this project.
 *
 */

#ifndef MACS_SERIAL_TYPES_H
#define MACS_SERIAL_TYPES_H

typedef unsigned long uint_t;		/**< \brief Unsigned integer type */
typedef void* serial_handle_t;		/**< \brief Data-type for an open serial device handle */

/** \brief Structure to store required serial properties. */
typedef struct
{
	uint_t baud_rate;	/**< \brief Transmission speed in bits per second (e.g., 9600). */
	uint_t timeout_ms;	/**< \brief Read/write timeout in milliseconds. */
} serial_properties_t;

#endif