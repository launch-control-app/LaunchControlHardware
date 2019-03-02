/*
  Creation Date: Tuesday, 29th January 2019 
  Original Author: Christian Francisco 
  Contents of File: Main loop of the program to poll a vehicle over OBD
  and transmit via bluetooth
*/

#include <sstream>

#include <Arduino.h>

#include "hardware/obd_uart.hpp"
#include "hardware/bluetooth.hpp"
#include "hardware/breakpoint_counter.hpp"
#include "obd/io.hpp"
#include "obd/profile.hpp"
#include "debug/log.hpp"

#define BT_SERIAL Serial4 // Serial4 uses pins 31 (RX) and 32 (TX)
#define BT_BAUD 9600      // OPTIONAL: change to Serial2 and 460800
                          //  for faster data transfer
#define BT_CMD 24         // TODO: make the defines constant variables
#define BT_STATE 25

hardware::ObdUart::Pids_t pids =
    {PID_RPM, PID_ENGINE_LOAD, PID_COOLANT_TEMP, PID_ABSOLUTE_ENGINE_LOAD,
     PID_ENGINE_OIL_TEMP, PID_ENGINE_TORQUE_PERCENTAGE, PID_ENGINE_REF_TORQUE,
     PID_INTAKE_TEMP, PID_INTAKE_MAP, PID_MAF_FLOW, PID_BAROMETRIC,
     PID_SPEED, PID_RUNTIME, PID_DISTANCE,
     PID_THROTTLE, PID_AMBIENT_TEMP,
     PID_CONTROL_MODULE_VOLTAGE,
     PID_FUEL_LEVEL};

hardware::ObdUart obd_uart;
hardware::Bluetooth bluetooth(BT_SERIAL, BT_CMD, BT_STATE, BT_BAUD);
hardware::BreakpointCounter &breakpoint_counter = hardware::BreakpointCounter::get_instance();
obd::Io io(bluetooth, obd_uart, breakpoint_counter);

void setup()
{
    obd_uart.begin();
    bluetooth.begin();
    obd::Profile profile;
    for (const auto& pid : pids)
        profile.add_pid(pid, 1000);
   io.load_profile(profile);
}

void loop()
{
    if (bluetooth.is_connected())
        debug::Log::info("connected");
    else
        debug::Log::info("not connected");
    hardware::ObdUart::Pids_and_values_t pid_values = obd_uart.read_pids(pids);
    std::stringstream output;
    for (const auto& pid_value : pid_values)
        output << pid_value.value << ",";
    bluetooth.transmit(output.str());
    delay(1000);
}