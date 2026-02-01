#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "../io.h"


void serial_reset(serial_handle_t hSerial)
{
    if (hSerial == NULL)
        return;

    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

    EscapeCommFunction((serial_handle_t)hSerial, SETDTR);
    
    Sleep(100); // Wait 100ms (Standard reset pulse duration)

    EscapeCommFunction((serial_handle_t)hSerial, CLRDTR);
    
    Sleep(200); // Wait for bootloader to initialize
}


serial_handle_t serial_open(uint_t port_no, uint_t baud_rate, uint_t timeout_ms)
{
    serial_handle_t hSerial;
    char devpath[MAX_PATH];

    if (port_no > PORT_MAX || port_no < PORT_MIN)
        return NULL;

    snprintf(devpath, MAX_PATH, "\\\\.\\COM%u", port_no);
    hSerial = CreateFile(
                        devpath, 
                        GENERIC_READ | GENERIC_WRITE, 
                        0,
                        NULL, 
                        OPEN_EXISTING, 
                        FILE_ATTRIBUTE_NORMAL, 
                        NULL
                    );

    if (hSerial == INVALID_HANDLE_VALUE)
        return NULL;

    serial_reset(hSerial);

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(hSerial, &dcb))
    {
        CloseHandle(hSerial);
        return NULL;
    }

    dcb.BaudRate = baud_rate;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    dcb.fBinary  = TRUE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl  = DTR_CONTROL_DISABLE;
    dcb.fRtsControl  = RTS_CONTROL_DISABLE;
    dcb.fOutX        = FALSE;
    dcb.fInX         = FALSE;

    if (!SetCommState(hSerial, &dcb))
    {
        CloseHandle(hSerial);
        return NULL;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadTotalTimeoutConstant = timeout_ms;

    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        CloseHandle(hSerial);
        return NULL;
    }

    return hSerial;
}


int serial_read(serial_handle_t hSerial, char *buf, uint_t count)
{
    /* count must not exceed sizeof(buf) - 1, where the index
     * sizeof(buf) - 1 is reserved for the null terminator.
     * That is, count <= (sizeof(buf) - 1)
     * There is no protection for this, so be careful. Also,
     * sizeof(buf) = strlen(buf) + 1 (C string).
     * And, buf[sizeof(buf) - 1] == buf[strlen(buf)] == '\0'.
     */

    if (hSerial == NULL)
        return 0;

    luint_t bytes_read = 0;
    BOOL status = ReadFile(
                    hSerial,
                    buf,
                    count,
                    &bytes_read, 
                    NULL
                );
    if (status == FALSE)
        return -1;

    buf[count] = '\0';

    return (int)bytes_read;
}


int serial_write(serial_handle_t hSerial, char *buf, uint_t count)
{
    /* buf must be a null-terminated character buffer (a string).
     * count <= (sizeof(buf) - 1) strictly, but there is
     * protection ensured here in this routine...
     */

    if (hSerial == NULL)
        return 0;

    uint_t max_chars = (uint_t)strlen(buf);
    count = (count > max_chars)? max_chars : count; // superman protection

    luint_t bytes_written = 0;
    BOOL status = WriteFile(
                    hSerial,
                    buf,
                    count,
                    &bytes_written, 
                    NULL
                );
    if (status == FALSE)
        return -1;

    return (int)bytes_written;
}


void serial_close(serial_handle_t hSerial)
{
    if (hSerial == NULL)
        return;

    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
    CloseHandle(hSerial);
}


int serial_readline(serial_handle_t hSerial, char *buf, uint_t buf_len)
{
    /* buf_len must be sizeof(buf) and NOT string length of buf. See
     * comments below serial_read().
     */

    uint_t i = 1;
    serial_read(hSerial, buf, 1);

    while (i < (buf_len - 1) && buf[i - 1] != '\n')
    {
        serial_read(hSerial, buf + i, 1);
        i++;
    }

    if (buf[i - 1] != '\n' && i == buf_len - 1)
        return -1; // End of buffer (line incomplete)

    memset(buf + i, 0, buf_len - i);    // zero out remaining buffer

    return i; // return the line size
}
