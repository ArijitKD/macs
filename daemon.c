#include <stdio.h>
#include <string.h>
#include "serial/macs.h"


int main(int argc, char *argv[])
{
    uint_t state = MACS_STATE_ON;
    if (argc > 1 && strcmp(argv[1], "off") == 0)
    {
        printf("New state = OFF\n");
        state = MACS_STATE_OFF;
    }
    else if (argc > 1 && strcmp(argv[1], "on") == 0)
    {
        printf("New state = ON\n");
    }
    else
    {
        printf("Bad flag or no flag (only \'on\' or \'off\' accepted).\n");
        return 1;
    }

    int macs_port, errcode;
    update_macs_state(state, &macs_port, &errcode);

    switch (errcode)
    {
        case MACS_ERR_NO_DEVICE:
            printf("Error: No MACS device found!!!\nFailed to change state.\n");
            return 1;
        
        case MACS_ERR_WRITE_FAILURE:
            printf("MACS device detected at port: COM%d\n", macs_port);
            printf("Error: Write failure on device!!!\nFailed to change state.\n");
            return 1;
        
        default:
            printf("MACS device detected at port: COM%d\n", macs_port);
            printf("Successfully changed state.\n");
    }
 
    return 0;
}