#define MACS_THERMAL_MONITOR_DLL_EXPORT
#include "thermalmonitor.h"

#include <windows.h>
#include <vcclr.h>


#using <LibreHardwareMonitorLib.dll>
using namespace LibreHardwareMonitor::Hardware;
static gcroot<Computer^> g_computer;


int thermalmonitor_init()
{
    try
    {
        g_computer = gcnew Computer();
        g_computer->IsCpuEnabled = true;
        g_computer->Open();
        return 0;
    }
    catch (...)
    {
        return -1;
    }
}


float get_cpu_temp()
{
    if (!g_computer)
        return -1.0f;
    g_computer->Hardware[0]->Update();
    for (int i = 0; i < g_computer->Hardware[0]->Sensors->Count; i++)
    {
        ISensor^ s = g_computer->Hardware[0]->Sensors[i];
        if (s->SensorType == SensorType::Temperature && s->Name == "Core Average")
        {
            return (float)s->Value.GetValueOrDefault();
        }
    }
    return 0.0f;
}


void thermalmonitor_close()
{
    if (g_computer)
    {
        g_computer->Close();
        g_computer = nullptr;
    }
}