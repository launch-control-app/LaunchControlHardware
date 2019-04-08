// platformio device monitor > final_trip.txt

#include <Arduino.h>

#include <sstream>
#include <list>

#include <OBD2UART.h>

#define BT_SERIAL Serial2 // Serial4 uses pins 31 (RX) and 32 (TX)
#define BT_BAUD 9600      // OPTIONAL: change to Serial2 and 460800 \
                          //  for faster data transfer
#define BT_CMD 24         // TODO: make the defines constant variables
#define BT_STATE 25

byte pids[] =
    {PID_RPM, PID_ENGINE_LOAD, PID_COOLANT_TEMP, PID_ABSOLUTE_ENGINE_LOAD,
     PID_ENGINE_OIL_TEMP, PID_ENGINE_TORQUE_PERCENTAGE, PID_ENGINE_REF_TORQUE,
     PID_INTAKE_TEMP, PID_INTAKE_MAP, PID_MAF_FLOW, PID_BAROMETRIC,
     PID_SPEED, PID_RUNTIME, PID_DISTANCE,
     PID_THROTTLE, PID_AMBIENT_TEMP,
     PID_CONTROL_MODULE_VOLTAGE,
     PID_FUEL_LEVEL};

struct supported_pid
{
    supported_pid(byte pid, bool supported) : pid(pid), supported(supported) {}
    byte pid;
    bool supported;
};
std::list<supported_pid> supported_pids;

std::stringstream output;
COBD obd;
char vin[64];
// bool flag = false;

void setup()
{
    delay(1000);
    Serial.begin(9600);
    BT_SERIAL.begin(BT_BAUD);
    obd.begin();
    do
    {
        Serial.println("DEBUG: Attempting to connect OBD");
    } while (!obd.init());
    obd.getVIN(vin, 64);
    
    for (const auto &pid : pids)
    {
        int result;
        bool supported = obd.readPID(pid, result);
        if (!supported)
            Serial.printf("DEBUG: PID %x not supported! \n", pid);
        supported_pids.emplace_back(pid, supported);
    }
}

void loop()
{
    Serial.println("DEBUG: Start of loop");
    output << vin;
    for (const auto &pid : supported_pids)
    {
        int result = -999; // error code
        if (pid.supported)
            obd.readPID(pid.pid, result);
        output << "," << result;
    }
    BT_SERIAL.println(output.str().c_str());
    Serial.println(output.str().c_str());
    output.str("");
    delay(300);

    // if (flag)
    // {
    //     BT_SERIAL.println("1,1,1,1,1,1,1");
    //     flag = false;
    // }
    // else
    // {
    //     BT_SERIAL.println("0,0,0,0,0,0,0,0");
    //     flag = true;
    // }
    // delay(1000);
}