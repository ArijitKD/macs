/**
 * \file errcodes.h
 *
 * \brief This header contains all errorcode-specific macros used throughout the project.
 *
 * By default most functions return -1 in case of an error. Such functions perform
 * a single dedicated task (such as read or write) and hence failure cause is deterministic.
 * However, in case a function performs multiple tasks internally, then such a function may
 * use error codes. Such functions should accept a pointer (int *errcode) to store the
 * error code. The return value, if applicable, could be anything as deemed appropriate.
 *
 */

#ifndef MACS_SERIAL_ERRCODES_H
#define MACS_SERIAL_ERRCODES_H

#define MACS_ERR_NO_DEVICE          -2                  /**< \brief Error code for no device detected */
#define MACS_ERR_WRITE_FAILURE      -3                  /**< \brief Error code denoting write failure */

#endif