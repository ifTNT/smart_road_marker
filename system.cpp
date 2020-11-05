#include "include/system.h"
#include "include/car_sensor_ir.h"
#include "include/reporter_bc20.h"
#include <Arduino.h>

/* =========================
 *  System module section
 * =========================
 */

// The sensor that return the traffic and average speed data.
CarSensor* carSensor = new CarSensorIR(A4, A5);

// The reporter that transmit the produced report data to backend.
Repoter* repoter = new ReporterBC20(Serial);

// Assign the software serial port for debugging purpose
#define DEBUG_SERIAL_RX_PIN 8
#define DEBUG_SERIAL_TX_PIN 9
SoftwareSerial DebugSoftwareSerial=
    SoftwareSerial(DEBUG_SERIAL_RX_PIN, DEBUG_SERIAL_TX_PIN);

/* =========================
 *  Global varible section
 * ========================= 
 */

// The system time of last report publishment
unsigned long long lastPublishTime;

// The error code storage place which is frequently used in the code.
int err = 0;