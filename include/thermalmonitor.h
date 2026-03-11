#ifndef MACS_THERMAL_MONITOR_H
#define MACS_THERMAL_MONITOR_H

#define USING_LIBRE_HARDWARE_MONITOR_LIB

#ifdef __cplusplus
extern "C" {
#endif

    #ifdef MACS_THERMAL_MONITOR_DLL_EXPORT
        #define MACS_THERMAL_MONITOR __declspec(dllexport)
    #else
        #define MACS_THERMAL_MONITOR __declspec(dllimport)
    #endif

    MACS_THERMAL_MONITOR int thermalmonitor_init();
    MACS_THERMAL_MONITOR float get_cpu_temp();
    MACS_THERMAL_MONITOR void thermalmonitor_close();

#ifdef __cplusplus
}
#endif

#endif